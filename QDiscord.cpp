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

#include "stdafx.h"
#include "moc_QDiscord.cpp"
#include "QDiscord.h"


QDiscord::QDiscord(QObject* parent)
	: QObject(parent)
{
	_ws.setState(&_state);
	connect(&_ws, &QDiscordWs::loggedIn, this, &QDiscord::wsConnectSuccess);
	connect(&_ws, &QDiscordWs::authFail, this, &QDiscord::wsConnectFailed);
	connect(&_ws, &QDiscordWs::disconnected, this, &QDiscord::wsDisconnected);
}


void QDiscord::login(const QDiscordToken& token)
{
	if (isConnected() || isConnecting())
	{
		return;
	}
	setToken(token);
	qCDebug(MAIN, ) << "getting gateway";
	QDiscordWs::getGateway(_rest, [this](QString endpoint)
	{
		if(endpoint.isEmpty())
		{
			qCDebug(MAIN, ) << "getting gateway failed";
			wsConnectFailed();
			return;
		}
		qCDebug(MAIN, ) << "opening WS to" << endpoint;
		_ws.open(endpoint);
	});
	_connecting = true;
}


void QDiscord::login(const QDiscordToken& token, const std::function<void(bool)>& callback)
{
	if (isConnected() || isConnecting())
	{
		return;
	}
	_loginCallback = callback;
	login(token);
}


void QDiscord::logout()
{
	if (!isConnected() && !isConnecting())
	{
		return;
	}
	_ws.close();
}


void QDiscord::logout(const std::function<void()>& callback)
{
	if (!isConnected() && !isConnecting())
	{
		return;
	}
	_logoutCallback = callback;
	logout();
}


QDiscordUserAgent QDiscord::userAgent() const
{
	return _rest.userAgent();
}


void QDiscord::setUserAgent(const QDiscordUserAgent& userAgent)
{
	_rest.setUserAgent(userAgent);
	_ws.setUserAgent(userAgent);
}


bool QDiscord::isConnecting() const
{
	return _connecting;
}


bool QDiscord::isConnected() const
{
	return _connected;
}


void QDiscord::setToken(const QDiscordToken& token)
{
	_ws.setToken(token);
	_rest.setToken(token);
}


void QDiscord::wsConnectFailed()
{
	_connecting = false;
	_connected = false;
	if(_loginCallback)
	{
		_loginCallback(false);
		_loginCallback = std::function<void(bool)>();
	}
	qCDebug(MAIN, ) << "login failed";
	emit loginFailed();
}


void QDiscord::wsDisconnected()
{
	_connecting = false;
	_connected = false;
	if(_logoutCallback)
	{
		_logoutCallback();
		_logoutCallback = std::function<void()>();
	}
	qCDebug(MAIN, ) << "logged out";

	emit loggedOut();
}


void QDiscord::wsConnectSuccess()
{
	_connecting = false;
	_connected = true;

	if(_loginCallback)
	{
		_loginCallback(true);
		_loginCallback = std::function<void(bool)>();
	}
	qCDebug(MAIN, ) << "logged in";
	emit loggedIn();
}


void QDiscord::Close()
{
	_ws.Close();
}

