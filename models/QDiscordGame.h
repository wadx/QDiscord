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

#include "QDiscordModel.h"


///\brief Represents a game object in the Discord API.
class QDiscordGame : public QDiscordModelBase<QDiscordGame>
{
	Q_GADGET

	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QString url READ url WRITE setUrl)
	Q_PROPERTY(QDiscordGame::GameType type READ type WRITE setType)

public:
	static QSharedPointer<QDiscordGame> fromJson(const QJsonObject& object);
	/*!
	 * \brief An enum holding different game types.
	 * Usually set when streaming. If an enum is not contained here,
	 * UnknownType will be set.
	 */
	enum class GameType : qint8
	{
		Default   = 0,
		Streaming = 1,
		Unknown   = -1
	};
	Q_ENUM(GameType)

	/*!
	 * \brief Manual constructor for a game object. Defaults to an empty object.
	 * \param name The game you wish to display for the status.
	 * \param url The game URL for your status. Usually only used when
	 * streaming.
	 * \param type The game type. Set this if you wish to show a streaming
	 * status.
	 */
	QDiscordGame(QString name, QString url = QString(), GameType type = GameType::Default);
	QDiscordGame() = default;
	///\brief Creates an instance from the provided JSON object.
	QDiscordGame(const QJsonObject& object);
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;
	///\brief Returns the game name of this object.
	QString name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	///\brief Returns the URL of this game object.
	QString url() const { return _url; }
	void setUrl(const QString& url) { _url = url; }
	///\brief Returns the type of this game object.
	GameType type() const { return _type; }
	void setType(GameType type) { _type = type; }
	bool isNull() const;
	operator bool() const;
	bool operator==(const QDiscordGame& other) const;
	bool operator!=(const QDiscordGame& other) const;
	bool operator<(const QDiscordGame& other) const;
	bool operator>(const QDiscordGame& other) const;
	bool operator<=(const QDiscordGame& other) const;
	bool operator>=(const QDiscordGame& other) const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		field(a, self._name, "name");
		field(a, self._url, "url");
		field(a, self._type, "type");
	}

private:
	QString  _name;
	QString  _url;
	GameType _type = GameType::Unknown;
};

Q_DECLARE_METATYPE(QDiscordGame)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGame::GameType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGame::GameType& value, const QString& name);
} // namespace QDiscordModel


