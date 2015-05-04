#include <QString>
#include <QtTest>
#include <QJsonObject>
#include <QSignalSpy>
#include <QList>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>

#include "communicationhandler.h"

class ServerTest : public QObject
{
    Q_OBJECT

public:
    ServerTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSuccessfulAuthenticationFlow();

    void testUnsuccessfulAuthFlow();
    void testSearchRequestQueryResponseMatchesQuery();
    void testSearchResponseMatchesExpectedResult();
private:
    CommunicationHandler *comm;
    void sendSuccessfulAuth();
};

ServerTest::ServerTest()
{

}

void ServerTest::init()
{
    comm = new CommunicationHandler("ws://192.168.2.18:8900");
    QSignalSpy initSpy(comm, SIGNAL(commConnected()));
    QVERIFY(initSpy.isValid());

    QTest::qWait(250);
    QCOMPARE(initSpy.count(), 1);
}

void ServerTest::cleanup()
{
    comm->deleteLater();
}

void ServerTest::testSearchResponseMatchesExpectedResult()
{
    QSignalSpy searchSpy(comm, SIGNAL(onSearchReceived(QJsonObject)));
    QVERIFY(searchSpy.isValid());

    comm->sendSearchRequest("Flo Rida");
    QTest::qWait(3000);

    QCOMPARE(searchSpy.count(), 1);
    QList<QVariant> args = searchSpy.takeFirst();

    QJsonObject obj = args.at(0).toJsonObject();
    QJsonObject res = obj["response"].toObject()["results"].toObject();

    QCOMPARE(res["number"].toInt(), 11);
    QJsonObject test
    {
        {"hash", "AwKakwe3NoIgrKU="},
        {"order", ""}
    };

    QJsonObject metadata
    {
        {"album", "My House"},
        {"artist", "Flo Rida Feat. Sage The Gemini"},
        {"genre", "Hip-Hop, Trap"},
        {"length", "3:08"},
        {"title", "G.D.F.R. (Going Down For Real)"},
        {"track_number", 6}
    };

    test["metadata"] = metadata;

    QJsonObject first = obj["response"]
                       .toObject()["results"]
                       .toObject()["results"]
                       .toArray()
                       .at(0)
                       .toObject();
    QVERIFY(test == first);
}

void ServerTest::sendSuccessfulAuth()
{
    QSignalSpy authSpy(comm, SIGNAL(onAuthReceived(bool)));
    QVERIFY(authSpy.isValid());
    comm->sendAuthRequest("serverPass");
    QTest::qWait(500);

    QCOMPARE(authSpy.count(), 1);
    QList<QVariant> args = authSpy.takeFirst();

    QVERIFY(args.at(0).toBool() == true);
}

void ServerTest::testSearchRequestQueryResponseMatchesQuery()
{
    // need to create successful auth request every time
    sendSuccessfulAuth();

    QSignalSpy searchSpy(comm, SIGNAL(onSearchReceived(QJsonObject)));
    QVERIFY(searchSpy.isValid());

    QString queryStr = "Flo Rida";

    comm->sendSearchRequest(queryStr);
    QTest::qWait(3000);

    QCOMPARE(searchSpy.count(), 1);
    QList<QVariant> args = searchSpy.takeFirst();

    QJsonObject obj = args.at(0).toJsonObject();

    QJsonObject res = obj["response"].toObject();

    QCOMPARE(res["query"].toString(), queryStr);
}

void ServerTest::testSuccessfulAuthenticationFlow()
{
    QSignalSpy spy(comm, SIGNAL(onAuthReceived(bool)));
    QVERIFY(spy.isValid());

    comm->sendAuthRequest("serverPass");

    QTest::qWait(250);

    QCOMPARE(spy.count(), 1);
    QList<QVariant> args = spy.takeFirst();

    QVERIFY(args.at(0).toBool() == true);
}

void ServerTest::testUnsuccessfulAuthFlow()
{
    QSignalSpy spy(comm, SIGNAL(onAuthReceived(bool)));
    QSignalSpy disconnect(comm, SIGNAL(connectionLost()));
    QVERIFY(spy.isValid());
    QVERIFY(disconnect.isValid());

    comm->sendAuthRequest("definitelyNotThePassword");

    QTest::qWait(250);

    QCOMPARE(spy.count(), 0);

    QTest::qWait(5000);
    QList<QVariant> args = spy.takeFirst();

    QVERIFY(args.at(0).toBool() == false);
    QVERIFY(disconnect.count() > 0);
}

QTEST_GUILESS_MAIN(ServerTest)

#include "tst_server.moc"
