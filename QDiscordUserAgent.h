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


class QDiscordLibraryVersion
{
	Q_GADGET

	Q_PROPERTY(QString version MEMBER version)
	Q_PROPERTY(quint16 majorVersion MEMBER majorVersion)
	Q_PROPERTY(quint16 minorVersion MEMBER minorVersion)
	Q_PROPERTY(quint16 patchVersion MEMBER patchVersion)

public:
	QString version;
	quint16 majorVersion = 0;
	quint16 minorVersion = 0;
	quint16 patchVersion = 0;
};
Q_DECLARE_METATYPE(QDiscordLibraryVersion)


class QDiscordUserAgent
{
	Q_GADGET

	Q_PROPERTY(QString libraryName READ libraryName WRITE setLibraryName)
	Q_PROPERTY(QString libraryLink READ libraryLink WRITE setLibraryLink)
	Q_PROPERTY(QDiscordLibraryVersion libraryVersion READ libraryVersion WRITE
				   setLibraryVersion)
	Q_PROPERTY(QString botName READ botName WRITE setBotName)

public:
	Q_INVOKABLE static const QDiscordUserAgent& global();
	QString libraryName() const { return _libraryName; }
	void setLibraryName(const QString& libraryName) { _libraryName = libraryName; }
	QString libraryLink() const { return _libraryLink; }
	void setLibraryLink(const QString& libraryLink) { _libraryLink = libraryLink; }
	QDiscordLibraryVersion libraryVersion() const { return _libraryVersion; }
	void setLibraryVersion(const QDiscordLibraryVersion& libraryVersion) { _libraryVersion = libraryVersion; }
	QString botName() const { return _botName; }
	void setBotName(const QString& botName) { _botName = botName; }
	Q_INVOKABLE QString toString() const;

private:
	static QDiscordUserAgent makeGlobalInstance();

	QString                _libraryName;
	QString                _libraryLink;
	QDiscordLibraryVersion _libraryVersion;
	QString                _botName;
};
Q_DECLARE_METATYPE(QDiscordUserAgent)


