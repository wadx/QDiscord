/*
 * QDiscord - An unofficial C++ and Qt wrapper for the Discord API.
 * Copyright (C) 2016-2017 george99g
 * Copyright(c) 2022 by wad(wad@inbox.lv)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "QDiscordAbstractState.h"
#include "QDiscordJsonDecoder.h"
#include "QDiscordToken.h"
#include "QDiscordUserAgent.h"

class QDiscordRest;


class QDiscordWs : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Error error READ error)
	Q_PROPERTY(QString errorString READ errorString STORED false)
	Q_PROPERTY(quint8 version READ version WRITE setVersion)
	Q_PROPERTY(Encoding encoding READ encoding WRITE setEncoding)
	Q_PROPERTY(int maxReconnectTime READ maxReconnectTime WRITE setMaxReconnectTime)
	Q_PROPERTY(int reconnectTime READ reconnectTime)
	Q_PROPERTY(int maxReconnectAttempts READ maxReconnectAttempts WRITE setMaxReconnectAttempts)
	Q_PROPERTY(int reconnectAttempt READ reconnectAttempt)
	Q_PROPERTY(QDiscordToken token READ token WRITE setToken)
	Q_PROPERTY(QString sessionId READ sessionId)
	Q_PROPERTY(quint32 latestSequence READ latestSequence)
	Q_PROPERTY(QDiscordAbstractState* state READ state WRITE setState)
	Q_PROPERTY(ConnectionState connectionState READ connectionState NOTIFY connectionStateChanged)
	Q_PROPERTY(QWebSocket* webSocket READ webSocketPtr)
	Q_PROPERTY(QDiscordUserAgent userAgent READ userAgent WRITE setUserAgent)

public:
	enum class GatewayOp : int
	{
		Dispatch            = 0,
		Heartbeat           = 1, // Used to maintain an active gateway connection. 
		Identify            = 2, // Used to trigger the initial handshake with the gateway.
		StatusUpdate        = 3, // Sent by the client to indicate a presence or status update.
		VoiceStateUpdate    = 4, // Sent when a client wants to join, move, or disconnect from a voice channel.
		VoiceServerPing     = 5,
		Resume              = 6, // Used to replay missed events when a disconnected client resumes.
		Reconnect           = 7, // The resumed event is dispatched when a client has sent a resume payload to the gateway (for resuming existing sessions).
		RequestGuildMembers = 8, // Used to request all members for a guild or a list of guilds. 
		InvalidSession      = 9, // Sent to indicate one of at least three different situations
		Hello               = 10, // Sent on connection to the websocket. Defines the heartbeat interval that the client should heartbeat to.
		HeartbeatAck        = 11
	};
	Q_ENUM(GatewayOp)

	enum class Encoding : quint8
	{
		JSON = 0,
		ETF  = 1
	};
	Q_ENUM(Encoding)

	enum class ConnectionState : quint8
	{
		Disconnected             = 0,
		UnexpectedlyDisconnected = 1,
		Connecting               = 2,
		Connected                = 3,
		HelloReceived            = 4,
		IdentifySent             = 5,
		ResumeSent               = 6,
		Authenticated            = 7,
		Disconnecting            = 8
	};
	Q_ENUM(ConnectionState)

	enum class Error : quint8
	{
		NoError              = 0,
		AlreadyConnected     = 1,
		NotConnected         = 2,
		EncodingNotSupported = 3,
		NoToken              = 4,
		WebSocketError       = 5,
		UnknownError         = 255
	};
	Q_ENUM(Error)

	static void getGateway(QDiscordRest& rest, const std::function<void(QString)>& callback);
	explicit QDiscordWs(QDiscordAbstractState* state = nullptr, QObject* parent = nullptr);
	Q_INVOKABLE bool open(const QString& endpoint, const QDiscordToken& token = QDiscordToken());
	Q_INVOKABLE bool open(QUrl endpoint, const QDiscordToken& token = QDiscordToken());
	Q_INVOKABLE void close(QWebSocketProtocol::CloseCode closeCode = QWebSocketProtocol::CloseCodeNormal);
	Q_INVOKABLE void abort();
	Q_INVOKABLE void reconnect();
	Q_INVOKABLE qint64 sendTextMessage(const QString& message);
	Q_INVOKABLE qint64 sendBinaryMessage(const QByteArray& data);

	Error error() const { return _error; }
	QString errorString() const;
	quint8 version() const { return _version; }
	bool setVersion(quint8 version);
	Encoding encoding() const { return _encoding; }
	bool setEncoding(Encoding encoding);
	int maxReconnectTime() const { return _maxReconnectTime; }
	void setMaxReconnectTime(int maxReconnectTime) { _maxReconnectTime = maxReconnectTime; }
	int reconnectTime() const { return _reconnectTime; }
	int maxReconnectAttempts() const { return _maxReconnectAttempts; }
	void setMaxReconnectAttempts(int maxReconnectAttempts) { _maxReconnectAttempts = maxReconnectAttempts; }
	int reconnectAttempt() const { return _reconnectAttempt; }
	QDiscordToken token() const { return _token; }
	bool setToken(const QDiscordToken& token);
	QString sessionId() const { return _sessionId; }
	quint32 latestSequence() const { return _latestSequence; }
	QDiscordAbstractState* state() { return _state; }
	void setState(QDiscordAbstractState* state);
	ConnectionState connectionState() const { return _cState; }
	QWebSocket& webSocket() { return _ws; }
	QWebSocket* webSocketPtr() { return &_ws; }
	QDiscordUserAgent userAgent() const { return _userAgent; }
	void setUserAgent(const QDiscordUserAgent& userAgent) { _userAgent = userAgent; }

	void Close();
signals:
	void error(Error error);
	void loggedIn();
	void authFail();
	void connectionStateChanged(ConnectionState state);
	void disconnected();

private:
	void setCState(ConnectionState state);
	void wsConnected();
	void wsDisconnected();
	void wsError(QAbstractSocket::SocketError);
	void wsMessage(const QString& message);
	void dispatchHelloJson(const QJsonObject& object);
	void dispatchAck();
	void dispatchReconnect();
	void dispatchDispatchJson(const QJsonObject& obj, const QString& t_string);
	void dispatchInvalidSession();
	void heartbeatTick();
	void sendIdentify();
	void sendResume();

	Error                  _error = Error::NoError;
	quint8                 _version = 6;
	Encoding               _encoding = Encoding::JSON;
	QUrl                   _endpoint;
	QDiscordToken          _token;
	QString                _sessionId;
	qint32                 _latestSequence = -1;
	QDiscordAbstractState* _state;
	QDiscordJsonDecoder    _jsonDecoder;
	// QDiscordEtfDecoder  _etfDecoder;
	QDiscordUserAgent      _userAgent;
	ConnectionState        _cState = ConnectionState::Disconnected;
	ConnectionState        _lastCState = _cState;
	QWebSocket             _ws;
	QTimer                 _heartbeatTimer;
	int                    _reconnectTime = 100;
	int                    _maxReconnectTime = 60000;
	int                    _reconnectAttempt = 0;
	int                    _maxReconnectAttempts = -1;
	bool                   _ackReceived = true;
	bool                   _closed = false;
};


