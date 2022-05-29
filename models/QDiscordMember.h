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

#include "QDiscordUser.h"

class QDiscordGuild;
class QDiscordRest;


/*!
 * \brief Represents a guild member in the Discord API.
 *
 * This class contains a QDiscordUser object which provides more information
 * about the guild member.\n
 * You may acquire a pointer to it using QDiscordMember::user.
 */
class QDiscordMember
	: public QDiscordModelBase<QDiscordMember>
	, public QDiscordModel::CompareById<QDiscordMember>
{
	Q_GADGET

	Q_PROPERTY(QDiscordID dId READ id WRITE setId STORED false)
	Q_PROPERTY(QDiscordUser user READ constUser WRITE setUser)
	Q_PROPERTY(std::optional<QString> nickname READ nickname WRITE setNickname)
	Q_PROPERTY(QDateTime joinedAt READ joinedAt WRITE setJoinedAt)
	Q_PROPERTY(std::optional<bool> deaf READ deaf WRITE setDeaf)
	Q_PROPERTY(std::optional<bool> mute READ mute WRITE setMute)
	Q_PROPERTY(QSharedPointer<QDiscordGuild> guild READ guild WRITE setGuild)
	Q_PROPERTY(QString mentionUsername READ mentionUsername STORED false)
	Q_PROPERTY(QString mentionNickname READ mentionNickname STORED false)

public:
	static QSharedPointer<QDiscordMember> fromJson(const QJsonObject& object);
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord guild member.
	 * \param guild A pointer to the member's parent guild.
	 */
	QDiscordMember(const QJsonObject& object);
	QDiscordMember() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;
	void update(const QDiscordMember& other);

	///\brief Returns a reference to the user object contained by this object.
	QDiscordID id() const { return _user ? _user->id() : QDiscordID(); }
	void setId(const QDiscordID& id) { if(_user) _user->setId(id); }
	QSharedPointer<QDiscordUser> user() const { return _user; }
	void setUser(QSharedPointer<QDiscordUser> user) { _user = user; }
	///\brief Returns this member's nickname.
	std::optional<QString> nick() const { return _nick; }
	void setNick(const QString& nick) { _nick = nick; }
	///\brief Returns the date at which the member has joined the guild.
	QDateTime joinedAt() const { return _joinedAt; }
	void setJoinedAt(const QDateTime& joinedAt) { _joinedAt = joinedAt; }
	///\brief Returns whether the member has disabled their speakers.
	std::optional<bool> deaf() const { return _deaf; }
	void setDeaf(const std::optional<bool>& deaf) { _deaf = deaf; }
	void resetDeaf() { _deaf.reset(); }
	///\brief Returns whether the member has muted their microphone.
	std::optional<bool> mute() const { return _mute; }
	void setMute(const std::optional<bool> mute) { _mute = mute; }
	void resetMute() { _mute.reset(); }
	///\brief Returns a pointer to this object's parent guild.
	QSharedPointer<QDiscordGuild> guild() const { return _guild.toStrongRef(); }
	void setGuild(QWeakPointer<QDiscordGuild> guild) { _guild = guild; }
	///\brief Returns a string which allows you to mention this member using
	/// their  username.
	QString mentionUsername() const;
	///\brief Returns a string which allows you to mention this member using
	/// their  nickname.
	QString mentionNickname() const;

	bool operator==(const QDiscordMember& other) const;
	bool operator!=(const QDiscordMember& other) const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._user, "user");
		field(a, self._nick, "nick");
		field(a, self._avatar, "avatar");
		field(a, self._roles, "roles");
		field(a, self._joinedAt, "joined_at");
		field(a, self._premium_since, "premium_since");
		field(a, self._deaf, "deaf");
		field(a, self._mute, "mute");
		field(a, self._pending, "pending");
		field(a, self._communication_disabled_until, "communication_disabled_until");
		field(a, self._permissions, "permissions");
		field(a, self._flags, "flags");
		field(a, self._guild_id, "guild_id");
		field(a, self._hoisted_role, "hoisted_role");
	}

private:
	QSharedPointer<QDiscordUser> _user;                         // the user this guild member represents
	std::optional<QString>       _nick;                         // this user's guild nickname
	std::optional<QString>       _avatar;                       // the member's guild avatar hash
	QList<QDiscordID>            _roles;                        // array of role object ids
	QDateTime                    _joinedAt;                     // when the user joined the guild
	std::optional<QDateTime>     _premium_since;                // when the user started boosting the guild
	std::optional<bool>          _deaf;                         // whether the user is deafened in voice channels
	std::optional<bool>          _mute;                         // whether the user is muted in voice channels
	std::optional<bool>          _pending;                      // whether the user has not yet passed the guild's Membership Screening requirements
	std::optional<QDateTime>     _communication_disabled_until; // when the user's timeout will expire and the user will be able to communicate in the guild again, null or a time in the past if the user is not timed out
	std::optional<QString>       _permissions;                  // total permissions of the member in the channel, including overwrites, returned when in the interaction object
	int                          _flags = -1;                   // [undocumented]
	std::optional<QDiscordID>    _guild_id;                     // [undocumented]
	std::optional<QDiscordID>    _hoisted_role;                 // [undocumented]

	QWeakPointer<QDiscordGuild>  _guild;
};

Q_DECLARE_METATYPE(QDiscordMember)

