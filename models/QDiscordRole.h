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

#include "QDiscordId.h"
#include "QDiscordPermissions.h"

class QDiscordGuild;
class QDiscordRest;


class QDiscordRole
	: public QDiscordModelBase<QDiscordRole>
	, public QDiscordModel::CompareById<QDiscordRole>
{
	Q_GADGET

	Q_PROPERTY(QDiscordID dId READ id WRITE setId)
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(quint32 color READ color WRITE setColor)
	Q_PROPERTY(bool hoist READ hoist WRITE setHoist)
	Q_PROPERTY(int position READ position WRITE setPosition)
	Q_PROPERTY(QDiscordPermissions permissions READ permissions WRITE setPermissions)
	Q_PROPERTY(bool managed READ managed WRITE setManaged)
	Q_PROPERTY(bool mentionable READ mentionable WRITE setMentionable)
	Q_PROPERTY(QSharedPointer<QDiscordGuild> guild READ guild WRITE setGuild)
	Q_PROPERTY(bool isEveryone READ isEveryone STORED false)

public:
	static QSharedPointer<QDiscordRole> fromJson(const QJsonObject& object);

	QDiscordRole(const QJsonObject& object);
	QDiscordRole() = default;

	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	QDiscordID id() const { return _id; }
	void setId(QDiscordID id) { _id = id; }
	QString name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	quint32 color() const { return _color; }
	quint32 colour() const { return _color; }
	void setColor(quint32 color) { _color = color; }
	void setColour(quint32 colour) { _color = colour; }
	bool hoist() const { return _hoist; }
	void setHoist(bool hoist) { _hoist = hoist; }
	int position() const { return _position; }
	void setPosition(int position) { _position = position; }
	QDiscordPermissions permissions() const { return _permissions; }
	void setPermissions(QDiscordPermissions permissions) { _permissions = permissions; }
	bool managed() const { return _managed; }
	void setManaged(bool managed) { _managed = managed; }
	bool mentionable() const { return _mentionable; }
	void setMentionable(bool mentionable) { _mentionable = mentionable; }
	QSharedPointer<QDiscordGuild> guild() const { return _guild.lock(); }
	void setGuild(QWeakPointer<QDiscordGuild> guild) { _guild = guild; }

	bool isEveryone() const;

	QString mention() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._name, "name");
		field(a, self._color, "color");
		field(a, self._hoist, "hoist");
		field(a, self._position, "position");
		field(a, self._permissions, "permissions");
		field(a, self._managed, "managed");
		field(a, self._mentionable, "mentionable");
	}

private:
	QDiscordID                  _id;
	QString                     _name;
	quint32                     _color = 0;
	bool                        _hoist = false;
	int                         _position = -1;
	QDiscordPermissions         _permissions;
	bool                        _managed = false;
	bool                        _mentionable = false;
	QWeakPointer<QDiscordGuild> _guild;
};
Q_DECLARE_METATYPE(QDiscordRole)

