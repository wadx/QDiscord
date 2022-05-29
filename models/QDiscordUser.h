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
#include "QDiscordId.h"
#include "QDiscordDiscriminator.h"

class QDiscordRest;


class QDiscordUser
	: public QDiscordModelBase<QDiscordUser>
	, public QDiscordModel::CompareById<QDiscordUser>
{
	Q_GADGET

	Q_PROPERTY(QDiscordID dId READ id WRITE setId)
	Q_PROPERTY(QString username READ username WRITE setUsername)
	Q_PROPERTY(QDiscordDiscriminator discriminator READ discriminator WRITE setDiscriminator)
public:

	enum class PremiumType : qint8
	{
		NONE          = 0, 
		NITRO_CLASSIC = 1,
		NITRO         = 2,
		Unknown       = -1
	};
	Q_ENUM(PremiumType)

	enum class UserAccountFlags : quint32
	{
		STAFF                    = 1 << 0, // Discord Employee
		PARTNER                  = 1 << 1, // Partnered Server Owner
		HYPESQUAD                = 1 << 2, // HypeSquad Events Member
		BUG_HUNTER_LEVEL_1       = 1 << 3, // Bug Hunter Level 1
		HYPESQUAD_ONLINE_HOUSE_1 = 1 << 6, // House Bravery Member
		HYPESQUAD_ONLINE_HOUSE_2 = 1 << 7, // House Brilliance Member
		HYPESQUAD_ONLINE_HOUSE_3 = 1 << 8, // House Balance Member
		PREMIUM_EARLY_SUPPORTER  = 1 << 9, // Early Nitro Supporter
		TEAM_PSEUDO_USER         = 1 << 10, // User is a team
		BUG_HUNTER_LEVEL_2       = 1 << 14, // Bug Hunter Level 2
		VERIFIED_BOT             = 1 << 16, // Verified Bot
		VERIFIED_DEVELOPER       = 1 << 17, // Early Verified Bot Developer
		CERTIFIED_MODERATOR      = 1 << 18, // Discord Certified Moderator
		BOT_HTTP_INTERACTIONS    = 1 << 19, // Bot uses only HTTP interactions and is shown in the online member list
	};

	static QSharedPointer<QDiscordUser> fromJson(const QJsonObject& object);
	QDiscordUser(const QJsonObject& object);
	QDiscordUser() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;
	void update(QSharedPointer<QDiscordUser> other);

	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	const QString& username() const { return _username; }
	void setUsername(const QString& username) { _username = username; }
	const QDiscordDiscriminator& discriminator() const { return _discriminator; }
	void setDiscriminator(const QDiscordDiscriminator& discriminator) { _discriminator = discriminator; }
	const std::optional<QString>& avatar() const { return _avatar; }
	void setAvatar(const QString& avatar) { _avatar = avatar; }
	const std::optional<bool>& bot() const { return _bot; }
	void setBot(bool bot) { _bot = bot; }
	const std::optional<bool>& mfaEnabled() const { return _mfaEnabled; }
	void setMfaEnabled(bool mfaEnabled) { _mfaEnabled = mfaEnabled; }
	const std::optional<QString>& email() const { return _email; }
	void setEmail(const QString& email) { _email = email; }
	const std::optional<bool>& verified() const { return _verified; }
	void setVerified(bool verified) { _verified = verified; }
	QString mention() const;
	static QDiscordID parseMention(const QString& mention);

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._username, "username");
		field(a, self._discriminator, "discriminator");
		field(a, self._avatar, "avatar");
		field(a, self._bot, "bot");
		field(a, self._system, "system");
		field(a, self._mfaEnabled, "mfa_enabled");
		field(a, self._banner, "banner");
		field(a, self._accent_color, "accent_color");
		field(a, self._locale, "locale");
		field(a, self._verified, "verified");
		field(a, self._email, "email");
		field(a, self._flags, "flags");
		field(a, self._premium_type, "premium_type");
		field(a, self._public_flags, "public_flags");
	}

private:
	QDiscordID             _id;            // the user's id
	QString                _username;      // the user's username, not unique across the platform
	QDiscordDiscriminator  _discriminator; // the user's 4-digit discord-tag
	std::optional<QString> _avatar;        // the user's avatar hash
	std::optional<bool>    _bot;           // whether the user belongs to an OAuth2 application
	std::optional<bool>    _system;        // whether the user is an Official Discord System user (part of the urgent message system)
	std::optional<bool>    _mfaEnabled;    // whether the user has two factor enabled on their account
	std::optional<QString> _banner;        // the user's banner hash
	std::optional<int>     _accent_color;  // the user's banner color encoded as an integer representation of hexadecimal color code
	std::optional<QString> _locale;        // the user's chosen language option
	std::optional<bool>    _verified;      // whether the email on this account has been verified
	std::optional<QString> _email;         // the user's email
	std::optional<int>     _flags;         // the flags on a user's account (UserAccountFlags)
	std::optional<int>     _premium_type;  // the type of Nitro subscription on a user's account (PremiumType)
	std::optional<int>     _public_flags;  // the public flags on a user's account (UserAccountFlags)
};
Q_DECLARE_METATYPE(QDiscordUser)

