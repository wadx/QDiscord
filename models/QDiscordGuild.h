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
#include "QDiscordChannel.h"
#include "QDiscordMember.h"
#include "QDiscordRole.h"
#include "QDiscordEmoji.h"
#include "QDiscordVoiceState.h"
#include "QDiscordPresence.h"
#include "QDiscordStageInstance.h"
#include "QDiscordSticker.h"
#include "QDiscordGuildScheduledEvent.h"

class QDiscordRest;


class QDiscordWelcomeScreenChannel
	: public QDiscordModelBase<QDiscordWelcomeScreenChannel>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordWelcomeScreenChannel> fromJson(const QJsonObject& object);
	QDiscordWelcomeScreenChannel(const QJsonObject& object);
	QDiscordWelcomeScreenChannel() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._channel_id, "channel_id");
		field(a, self._description, "description");
		field(a, self._emoji_id, "emoji_id");
		field(a, self._emoji_name, "emoji_name");
	}

private:
	QDiscordID                _channel_id;  // the channel's id
	QString                   _description; // the description shown for the channel
	std::optional<QDiscordID> _emoji_id;    // the emoji id, if the emoji is custom
	std::optional<QString>    _emoji_name;  // the emoji name if custom, the unicode character if standard, or null if no emoji is set
};
Q_DECLARE_METATYPE(QDiscordWelcomeScreenChannel)


class QDiscordWelcomeScreen
	: public QDiscordModelBase<QDiscordWelcomeScreen>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordWelcomeScreen> fromJson(const QJsonObject& object);
	QDiscordWelcomeScreen(const QJsonObject& object);
	QDiscordWelcomeScreen() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._description, "description");
		field(a, self._welcome_channels, "welcome_channels");
	}

private:
	std::optional<QString>              _description;      // the server description shown in the welcome screen
	QList<QDiscordWelcomeScreenChannel> _welcome_channels; // the channels shown in the welcome screen, up to 5
};
Q_DECLARE_METATYPE(QDiscordWelcomeScreen)


class QDiscordGuild
	: public QEnableSharedFromThis<QDiscordGuild>
	, public QDiscordModelBase<QDiscordGuild>
	, public QDiscordModel::CompareById<QDiscordGuild>
{
	Q_GADGET

	Q_PROPERTY(QDiscordID dId READ id WRITE setId)
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QString icon READ icon WRITE setIcon)
	Q_PROPERTY(QString splash READ splash WRITE setSplash)
	Q_PROPERTY(QDiscordID ownerId READ ownerId WRITE setOwnerId)
	Q_PROPERTY(QDiscordID applicationId READ applicationId WRITE setApplicationId)
	Q_PROPERTY(QString region READ region WRITE setRegion)
	Q_PROPERTY(QDiscordID afkChannelId READ afkChannelId WRITE setAfkChannelId)
	Q_PROPERTY(int afkTimeout READ afkTimeout WRITE setAfkTimeout)
	Q_PROPERTY(VerificationLevel verificationLevel READ verificationLevel WRITE setVerificationLevel)
	Q_PROPERTY(NotificationLevel defaultMessageNotifications READ defaultMessageNotifications WRITE setDefaultMessageNotifications)
	Q_PROPERTY(ExplicitContentFilterLevel explicitContentFilter READ explicitContentFilter WRITE setExplicitContentFilter)
	Q_PROPERTY(QStringList features READ features WRITE setFeatures)
	Q_PROPERTY(int mfaLevel READ mfaLevel WRITE setMfaLevel)
	Q_PROPERTY(QDateTime joinedAt READ joinedAt WRITE setJoinedAt)
	Q_PROPERTY(std::optional<bool> large READ large WRITE setLarge)
	Q_PROPERTY(std::optional<bool> unavailable READ unavailable WRITE setUnavailable)
	Q_PROPERTY(int memberCount READ memberCount WRITE setMemberCount)
	Q_PROPERTY(QList<QSharedPointer<QDiscordRole>> roles READ roles STORED false)
	Q_PROPERTY(QList<QSharedPointer<QDiscordMember>> members READ members STORED false)
	Q_PROPERTY(QList<QSharedPointer<QDiscordChannel>> channels READ channels STORED false)

public:
	static QSharedPointer<QDiscordGuild> fromJson(const QJsonObject& object);

	enum class NotificationLevel : qint8
	{
		AllMessages  = 0,
		OnlyMentions = 1,
		Unknown      = -1
	};
	Q_ENUM(NotificationLevel)

	enum class VerificationLevel : qint8
	{
		None    = 0,
		Low     = 1,
		Medium  = 2,
		High    = 3,
		Unknown = -1
	};
	Q_ENUM(VerificationLevel)

	enum class ExplicitContentFilterLevel : qint8
	{
		None         = 0,
		WithoutRoles = 1,
		All          = 2,
		Unknown      = -1
	};
	Q_ENUM(ExplicitContentFilterLevel)

	enum class NSFWLevel : qint8
	{
		DEFAULT        = 0,
		EXPLICIT       = 1,
		SAFE           = 2,
		AGE_RESTRICTED = 3,
		Unknown        = -1
	};
	Q_ENUM(NSFWLevel)

	enum class PremiumTier : qint8
	{
		NONE    = 0, // guild has not unlocked any Server Boost perks
		TIER_1  = 1, // guild has unlocked Server Boost level 1 perks
		TIER_2  = 2, // guild has unlocked Server Boost level 2 perks
		TIER_3  = 3, // guild has unlocked Server Boost level 3 perks
		Unknown = -1
	};
	Q_ENUM(PremiumTier)

	enum class SystemChannelFlags : quint8
	{
		SUPPRESS_JOIN_NOTIFICATIONS           = 1 << 0, // Suppress member join notifications
		SUPPRESS_PREMIUM_SUBSCRIPTIONS        = 1 << 1, // Suppress server boost notifications
		SUPPRESS_GUILD_REMINDER_NOTIFICATIONS = 1 << 2, // Suppress server setup tips
		SUPPRESS_JOIN_NOTIFICATION_REPLIES    = 1 << 3  // Hide member join sticker reply buttons
	};

	QDiscordGuild(const QDiscordGuild& other);
	QDiscordGuild() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize();

	static void listMembers(QDiscordRest& rest, const QDiscordID& guild, uint16_t limit, const QDiscordID& after, const std::function<void(QList<QDiscordMember>)>& callback);

	///\brief Returns the guild's ID.
	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	///\brief Returns the guild's name.
	const QString& name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	const QString& icon() const { return _icon; }
	void setIcon(const QString& icon) { _icon = icon; }
	const QString& splash() const { return _splash; }
	void setSplash(const QString& splash) { _splash = splash; }
	const QDiscordID& ownerId() const { return _ownerId; }
	void setOwnerId(const QDiscordID& ownerId) { _ownerId = ownerId; }
	const QDiscordID& applicationId() const { return _applicationId; }
	void setApplicationId(const QDiscordID& applicationId) { _applicationId = applicationId; }
	const std::optional<QString>& region() const { return _region; }
	void setRegion(const QString& region) { _region = region; }
	const QDiscordID& afkChannelId() const { return _afkChannelId; }
	void setAfkChannelId(const QDiscordID& afkChannelId) { _afkChannelId = afkChannelId; }
	int afkTimeout() const { return _afkTimeout; }
	void setAfkTimeout(int afkTimeout) { _afkTimeout = afkTimeout; }
	VerificationLevel verificationLevel() const { return _verificationLevel; }
	void setVerificationLevel(VerificationLevel verificationLevel) { _verificationLevel = verificationLevel; }
	NotificationLevel defaultMessageNotifications() const { return _defaultMessageNotifications; }
	void setDefaultMessageNotifications(NotificationLevel defaultMessageNotifications) { _defaultMessageNotifications = defaultMessageNotifications; }
	ExplicitContentFilterLevel explicitContentFilter() const { return _explicitContentFilter; }
	void setExplicitContentFilter(ExplicitContentFilterLevel explicitContentFilter) { _explicitContentFilter = explicitContentFilter; }
	const QStringList& features() const { return _features; }
	void setFeatures(const QStringList& features) { _features = features; }
	int mfaLevel() const { return _mfaLevel; }
	void setMfaLevel(int mfaLevel) { _mfaLevel = mfaLevel; }
	const std::optional<bool>& unavailable() const { return _unavailable; }
	void setUnavailable(bool unavailable) { _unavailable = unavailable; }
	const std::optional<int>& memberCount() const { return _memberCount; }
	void setMemberCount(int memberCount) { _memberCount = memberCount; }
	void update(const QDiscordGuild& other);
	const QMap<QDiscordID, QSharedPointer<QDiscordRole>>& roles() const { return _roles; }
	const QMap<QDiscordID, QSharedPointer<QDiscordMember>>& members() const { return _members; }
	const QMap<QDiscordID, QSharedPointer<QDiscordChannel>>& channels() const { return _channels; }
	Q_INVOKABLE QSharedPointer<QDiscordRole> role(const QDiscordID& id) const { return _roles.value(id, QSharedPointer<QDiscordRole>()); }
	Q_INVOKABLE QSharedPointer<QDiscordChannel> channel(const QDiscordID& id) const { return _channels.value(id, QSharedPointer<QDiscordChannel>()); }
	Q_INVOKABLE QSharedPointer<QDiscordMember> member(const QDiscordID& id) const { return _members.value(id, QSharedPointer<QDiscordMember>()); }
	Q_INVOKABLE void addRole(const QSharedPointer<QDiscordRole>& role);
	Q_INVOKABLE bool removeRole(const QSharedPointer<QDiscordRole>& role);
	Q_INVOKABLE bool removeRole(QDiscordID role);
	Q_INVOKABLE void addChannel(const QSharedPointer<QDiscordChannel>& channel);
	Q_INVOKABLE bool removeChannel(const QSharedPointer<QDiscordChannel>& channel);
	Q_INVOKABLE bool removeChannel(const QDiscordID& channel);
	Q_INVOKABLE void addMember(const QSharedPointer<QDiscordMember>& member);
	Q_INVOKABLE bool removeMember(const QSharedPointer<QDiscordMember>& member);
	Q_INVOKABLE bool removeMember(const QDiscordID& member);
	const QString& preferred_locale() const { return _preferred_locale; }
	void setPreferred_locale(const QString& preferred_locale) { _preferred_locale = preferred_locale; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._unavailable, "unavailable");
		if (!self._unavailable.value_or(false))
		{
			field(a, self._name, "name");
			field(a, self._icon, "icon");
			field(a, self._icon_hash, "icon_hash");
			field(a, self._splash, "splash");
			field(a, self._discovery_splash, "discovery_splash");
			field(a, self._owner, "owner");
			field(a, self._ownerId, "owner_id");
			field(a, self._permissions, "permissions");
			field(a, self._region, "region");
			field(a, self._afkChannelId, "afk_channel_id");
			field(a, self._afkTimeout, "afk_timeout");
			field(a, self._widget_enabled, "widget_enabled");
			field(a, self._widget_channel_id, "widget_channel_id");
			field(a, self._verificationLevel, "verification_level");
			field(a, self._defaultMessageNotifications, "default_message_notifications");
			field(a, self._explicitContentFilter, "explicit_content_filter");
			field(a, self._features, "features");
			field(a, self._mfaLevel, "mfa_level");
			field(a, self._memberCount, "member_count");
			field(a, self._voice_states, "voice_states");
			field(a, self._applicationId, "application_id");
			field(a, self._system_channel_id, "system_channel_id");
			field(a, self._system_channel_flags, "system_channel_flags");
			field(a, self._rules_channel_id, "rules_channel_id");
			field(a, self._roles, "roles");
			field(a, self._emojis, "emojis");
			field(a, self._members, "members");
			field(a, self._channels, "channels");
			field(a, self._threads, "threads");
			field(a, self._presences, "presences");
			field(a, self._max_presences, "max_presences");
			field(a, self._max_members, "max_members");
			field(a, self._vanity_url_code, "vanity_url_code");
			field(a, self._description, "description");
			field(a, self._banner, "banner");
			field(a, self._premium_tier, "premium_tier");
			field(a, self._premium_subscription_count, "premium_subscription_count");
			field(a, self._preferred_locale, "preferred_locale");
			field(a, self._public_updates_channel_id, "public_updates_channel_id");
			field(a, self._max_video_channel_users, "max_video_channel_users");
			field(a, self._approximate_member_count, "approximate_member_count");
			field(a, self._approximate_presence_count, "approximate_presence_count");
			field(a, self._welcome_screen, "welcome_screen");
			field(a, self._nsfw_level, "nsfw_level");
			field(a, self._stage_instances, "stage_instances");
			field(a, self._stickers, "stickers");
			field(a, self._guild_scheduled_events, "guild_scheduled_events");
			field(a, self._premium_progress_bar_enabled, "premium_progress_bar_enabled");
			self.resolveRelationships();
		}
	}

private:
	void resolveRelationships();
	void resolveRelationships() const;

	QDiscordID                                        _id;
	QString                                           _name;
	QString                                           _icon;
	std::optional<QString>                            _icon_hash;                            // icon hash, returned when in the template object
	QString                                           _splash;                               // splash hash
	std::optional<QString>                            _discovery_splash;                     // discovery splash hash; only present for guilds with the "DISCOVERABLE" feature
	std::optional<bool>                               _owner;                                // true if the user is the owner of the guild
	QDiscordID                                        _ownerId;                              // id of owner
	std::optional<QDiscordPermissions>                _permissions;                          // total permissions for the user in the guild(excludes overwrites)
	std::optional<QString>                            _region;                               // voice region id for the guild (deprecated)
	QDiscordID                                        _afkChannelId;                         // id of afk channel
	int                                               _afkTimeout = -1;                      // afk timeout in seconds
	std::optional<bool>                               _widget_enabled;                       // true if the server widget is enabled
	std::optional<QDiscordID>                         _widget_channel_id;                    // the channel id that the widget will generate an invite to, or null if set to no invite
	VerificationLevel                                 _verificationLevel = VerificationLevel::Unknown;
	NotificationLevel                                 _defaultMessageNotifications = NotificationLevel::Unknown;
	ExplicitContentFilterLevel                        _explicitContentFilter = ExplicitContentFilterLevel::Unknown;
	QMap<QDiscordID, QSharedPointer<QDiscordRole>>    _roles;                                // roles in the guild
	QList<QDiscordEmoji>                              _emojis;                               // custom guild emojis
	QStringList                                       _features;                             // enabled guild features
	int                                               _mfaLevel = -1;                        // required MFA level for the guild
	QDiscordID                                        _applicationId;                        // application id of the guild creator if it is bot-created
	std::optional<QDiscordID>                         _system_channel_id;                    // the id of the channel where guild notices such as welcome messages and boost events are posted
	std::optional<int>                                _system_channel_flags;                 // system channel flags (SystemChannelFlags)
	std::optional<QDiscordID>                         _rules_channel_id;                     // the id of the channel where Community guilds can display rules and /or guidelines
	std::optional<int>                                _max_presences;                        // the maximum number of presences for the guild (null is always returned, apart from the largest of guilds)
	std::optional<int>                                _max_members;                          // the maximum number of members for the guild
	std::optional<QString>                            _vanity_url_code;                      // the vanity url code for the guild
	std::optional<QString>                            _description;                          // the description of a guild
	PremiumTier                                       _premium_tier = PremiumTier::Unknown;  // premium tier (Server Boost level)
	std::optional<int>                                _premium_subscription_count;           // the number of boosts this guild currently has
	QString                                           _preferred_locale;                     // the preferred locale of a Community guild; used in server discovery and notices from Discord, and sent in interactions; defaults to "en-US"
	std::optional<QDiscordID>                         _public_updates_channel_id;            // the id of the channel where admins and moderators of Community guilds receive notices from Discord
	std::optional<int>                                _max_video_channel_users;              // the maximum amount of users in a video channel
	std::optional<int>                                _approximate_member_count;             // approximate number of members in this guild, returned from the GET /guilds/<id> endpoint when with_counts is true
	std::optional<int>                                _approximate_presence_count;           // approximate number of non-offline members in this guild, returned from the GET /guilds/<id> endpoint when with_counts is true
	std::optional<QDiscordWelcomeScreen>              _welcome_screen;                       // the welcome screen of a Community guild, shown to new members, returned in an Invite's guild object
	NSFWLevel                                         _nsfw_level = NSFWLevel::Unknown;      // guild NSFW level
	QList<QDiscordSticker>                            _stickers;                             // custom guild stickers
	bool                                              _premium_progress_bar_enabled = false; // whether the guild has the boost progress bar enabled
	std::optional<int>                                _memberCount;
	QList<QDiscordVoiceState>                         _voice_states;                         // partial states of members currently in voice channels; lacks the guild_id key
	QMap<QDiscordID, QSharedPointer<QDiscordMember>>  _members;
	QMap<QDiscordID, QSharedPointer<QDiscordChannel>> _channels;
	QList<QDiscordChannel>                            _threads;                              // all active threads in the guild that current user has permission to view
	QList<QDiscordPresence>                           _presences;                            // presences of the members in the guild, will only include non-offline members if the size is greater than large threshold
	std::optional<QString>                            _banner;                               // banner hash
	QList<QDiscordStageInstance>                      _stage_instances;                      // Stage instances in the guild
	QList<QDiscordGuildScheduledEvent>                _guild_scheduled_events;               // the scheduled events in the guild
	std::optional<bool>                               _unavailable;                          // for partial guild object
};
Q_DECLARE_METATYPE(QDiscordGuild)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::VerificationLevel& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::VerificationLevel& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::NotificationLevel& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::NotificationLevel& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::ExplicitContentFilterLevel& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::ExplicitContentFilterLevel& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::NSFWLevel& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::NSFWLevel& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordGuild::PremiumTier& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordGuild::PremiumTier& value, const QString& name);
} // namespace QDiscordModel


