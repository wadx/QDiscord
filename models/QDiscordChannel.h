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
#include "QDiscordUser.h"
#include "QDiscordPermissionOverwrite.h"

class QDiscordMessage;
class QDiscordGuild;
class QDiscordRest;


class QDiscordThreadMetadata
	: public QDiscordModelBase<QDiscordThreadMetadata>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordThreadMetadata> fromJson(const QJsonObject& object);
	QDiscordThreadMetadata(const QJsonObject& object);
	QDiscordThreadMetadata() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._archived, "archived");
		field(a, self._auto_archive_duration, "auto_archive_duration");
		field(a, self._archive_timestamp, "archive_timestamp");
		field(a, self._locked, "locked");
		field(a, self._invitable, "invitable");
		field(a, self._create_timestamp, "create_timestamp");
	}

private:
	bool                     _archived = false;          // whether the thread is archived
	int                      _auto_archive_duration = 0; // duration in minutes to automatically archive the thread after recent activity, can be set to: 60, 1440, 4320, 10080
	QDateTime                _archive_timestamp;         // timestamp when the thread's archive status was last changed, used for calculating recent activity
	bool                     _locked = false;            // whether the thread is locked; when a thread is locked, only users with MANAGE_THREADS can unarchive it
	std::optional<bool>      _invitable;                 // whether non-moderators can add other non-moderators to a thread; only available on private threads
	std::optional<QDateTime> _create_timestamp;          // timestamp when the thread was created; only populated for threads created after 2022-01-09
};
Q_DECLARE_METATYPE(QDiscordThreadMetadata)


class QDiscordThreadMember
	: public QDiscordModelBase<QDiscordThreadMember>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordThreadMember> fromJson(const QJsonObject& object);
	QDiscordThreadMember(const QJsonObject& object);
	QDiscordThreadMember() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._user_id, "user_id");
		field(a, self._join_timestamp, "join_timestamp");
		field(a, self._flags, "flags");
	}

private:
	std::optional<QDiscordID> _id;             // the id of the thread
	std::optional<QDiscordID> _user_id;        // the id of the user
	QDateTime                 _join_timestamp; // the time the current user last joined the thread
	int                       _flags = 0;      // any user-thread settings, currently only used for notifications
};
Q_DECLARE_METATYPE(QDiscordThreadMember)


///\brief Represents either a private or guild channel in the Discord API.
class QDiscordChannel
	: public QDiscordModelBase<QDiscordChannel>
	, public QDiscordModel::CompareById<QDiscordChannel>
{
	Q_GADGET

	Q_PROPERTY(QDiscordID dId READ id WRITE setId)
	Q_PROPERTY(QDiscordChannel::Type type READ type WRITE setType)
	Q_PROPERTY(QDiscordID guildId READ guildId WRITE setGuildId)
	Q_PROPERTY(int position READ position WRITE setPosition)
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QString topic READ topic WRITE setTopic)
	Q_PROPERTY(QDiscordID lastMessageId READ lastMessageId WRITE setLastMessageId)
	Q_PROPERTY(int bitrate READ bitrate WRITE setBitrate)
	Q_PROPERTY(int userLimit READ userLimit WRITE setUserLimit)
	Q_PROPERTY(QList<QSharedPointer<QDiscordUser>> recipients READ recipients WRITE setRecipients)
	Q_PROPERTY(QString icon READ icon WRITE setIcon)
	Q_PROPERTY(QDiscordID ownerId READ ownerId WRITE setOwnerId)
	Q_PROPERTY(QDiscordID applicationId READ applicationId WRITE setApplicationId)
	Q_PROPERTY(QDiscordID parentId READ parentId WRITE setParentId)
	Q_PROPERTY(QSharedPointer<QDiscordChannel> parent READ parent WRITE setParent)
	Q_PROPERTY(QSharedPointer<QDiscordGuild> guild READ guild WRITE setGuild)
	Q_PROPERTY(QString mention READ mention STORED false)

public:
	/*!
	 * \brief An enumerator holding all possible types of channels.
	 * If a type is not defined here, `ChannelType::UnknownType` will be set.
	 * See https://discordapp.com/developers/docs/resources/channel#guild-channel-structure
	 * for more information.
	 */
	enum class Type : quint8
	{
		GUILD_TEXT           = 0, // a text channel within a server
		DM                   = 1, // a direct message between users
		GUILD_VOICE          = 2, // a voice channel within a server
		GROUP_DM             = 3,  // a direct message between multiple users
		GUILD_CATEGORY       = 4, // an organizational category that contains up to 50 channels
		GUILD_NEWS           = 5, // a channel that users can follow and crosspost into their own server
		GUILD_NEWS_THREAD    = 10, // a temporary sub-channel within a GUILD_NEWS channel
		GUILD_PUBLIC_THREAD  = 11, // a temporary sub-channel within a GUILD_TEXT channel
		GUILD_PRIVATE_THREAD = 12, // a temporary sub-channel within a GUILD_TEXT channel that is only viewable by those invited and those with the MANAGE_THREADS permission
		GUILD_STAGE_VOICE    = 13, // a voice channel for hosting events with an audience
		GUILD_DIRECTORY      = 14, // the channel in a hub containing the listed servers
		GUILD_FORUM          = 15, // (still in development) a channel that can only contain threads
		UnknownType          = 255
	};
	Q_ENUM(Type)

	enum class VideoQualityMode : quint8
	{
		AUTO = 1, // Discord chooses the quality for optimal performance
		FULL = 2, // 720p
	};
	Q_ENUM(VideoQualityMode)

	enum class ChannelFlags : quint8
	{
		PINNED = 1 << 1 // this thread is pinned to the top of its parent forum channel
	};

	static QSharedPointer<QDiscordChannel> fromJson(const QJsonObject& object);
	/*!
	 * \brief Creates an instance from the provided parameters.
	 * \param object A JSON object of a Discord channel.
	 * \param guild A pointer to the parent guild of the channel, if any.
	 * \note Some properties may be default, not accessible or `nullptr`,
	 * depending on what type() and isPrivate() return.
	 */
	QDiscordChannel(const QJsonObject& object);
	QDiscordChannel() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	static void get(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(QDiscordChannel)>& callback);
	static void getPrivateChannels(QDiscordRest& rest, const std::function<void(QList<QDiscordChannel>)>& callback);
	static void getMessage(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback);
	void getMessage(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback);
	static void getMessages(QDiscordRest& rest, const QDiscordID& channel, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void getMessages(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessages(QDiscordRest* rest, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessages(QDiscordRest* rest, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void getMessagesAfter(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void getMessagesAfter(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessagesAfter(QDiscordRest* rest, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessagesAfter(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void getMessagesBefore(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void getMessagesBefore(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessagesBefore(QDiscordRest* rest, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessagesBefore(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void getMessagesAround(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void getMessagesAround(QDiscordRest& rest, const QDiscordID& channel, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessagesAround(QDiscordRest* rest, const QDiscordID& message, int limit, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	void getMessagesAround(QDiscordRest* rest, const QDiscordID& message, const std::function<void(QList<QSharedPointer<QDiscordMessage>>)>& callback);
	static void modify(QDiscordRest& rest, const QDiscordID& channel, const QJsonObject& data);
	static void modify(QDiscordRest& rest, const QDiscordID& channel, const QJsonObject& data, const std::function<void(QDiscordChannel)>& callback);
	void modify(QDiscordRest* rest, const QJsonObject& data);
	void modify(QDiscordRest* rest, const QJsonObject& data, const std::function<void(QDiscordChannel)>& callback);
	static void modifyName(QDiscordRest& rest, const QDiscordID& channel, const QString& name);
	static void modifyName(QDiscordRest& rest, const QDiscordID& channel, const QString& name, const std::function<void(QDiscordChannel)>& callback);
	void modifyName(QDiscordRest* rest, const QString& name);
	void modifyName(QDiscordRest* rest, const QString& name, const std::function<void(QDiscordChannel)>& callback);
	static void modifyPosition(QDiscordRest& rest, const QDiscordID& channel, int position);
	static void modifyPosition(QDiscordRest& rest, const QDiscordID& channel, int position, const std::function<void(QDiscordChannel)>& callback);
	void modifyPosition(QDiscordRest* rest, int position);
	void modifyPosition(QDiscordRest* rest, int position, const std::function<void(QDiscordChannel)>& callback);
	static void modifyTopic(QDiscordRest& rest, const QDiscordID& channel, const QString& topic);
	static void modifyTopic(QDiscordRest& rest, const QDiscordID& channel, const QString& topic, const std::function<void(QDiscordChannel)>& callback);
	void modifyTopic(QDiscordRest* rest, const QString& topic);
	void modifyTopic(QDiscordRest* rest, const QString& topic, const std::function<void(QDiscordChannel)>& callback);
	static void modifyBitrate(QDiscordRest& rest, const QDiscordID& channel, int bitrate);
	static void modifyBitrate(QDiscordRest& rest, const QDiscordID& channel, int bitrate, const std::function<void(QDiscordChannel)>& callback);
	void modifyBitrate(QDiscordRest* rest, int bitrate);
	void modifyBitrate(QDiscordRest* rest, int bitrate, const std::function<void(QDiscordChannel)>& callback);
	static void modifyUserLimit(QDiscordRest& rest, const QDiscordID& channel, int userLimit);
	static void modifyUserLimit(QDiscordRest& rest, const QDiscordID& channel, int userLimit, const std::function<void(QDiscordChannel)>& callback);
	void modifyUserLimit(QDiscordRest* rest, int userLimit);
	void modifyUserLimit(QDiscordRest* rest, int userLimit, const std::function<void(QDiscordChannel)>& callback);
	static void triggerTyping(QDiscordRest& rest, const QDiscordID& channel);
	static void triggerTyping(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(bool)>& callback);
	void triggerTyping(QDiscordRest* rest);
	void triggerTyping(QDiscordRest* rest, const std::function<void(bool)>& callback);
	static void remove(QDiscordRest& rest, const QDiscordID& channel);
	static void remove(QDiscordRest& rest, const QDiscordID& channel, const std::function<void(QDiscordChannel)>& callback);
	void remove(QDiscordRest* rest);
	void remove(QDiscordRest* rest, const std::function<void(QDiscordChannel)>& callback);

	QDiscordID id() const { return _id; }
	void setId(QDiscordID id) { _id = id; }
	Type type() const { return _type; }
	void setType(Type type) { _type = type; }
	std::optional<QDiscordID> guildId() const { return _guildId; }
	void setGuildId(QDiscordID guildId) { _guildId = guildId; }
	///\brief Returns the channel's position in the channel list.
	std::optional<int> position() const { return _position; }
	void setPosition(int position) { _position = position; }
	///\brief Returns the channel's name.
	std::optional<QString> name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	///\brief Returns the channel's topic.
	std::optional<QString> topic() const { return _topic; }
	void setTopic(const QString& topic) { _topic = topic; }
	///\brief Returns the ID of the last sent message.
	std::optional<QDiscordID> lastMessageId() const { return _lastMessageId; }
	void setLastMessageId(QDiscordID lastMessageId) { _lastMessageId = lastMessageId; }
	///\brief Returns the channel's bitrate
	std::optional<int> bitrate() const { return _bitrate; }
	void setBitrate(int bitrate) { _bitrate = bitrate; }
	///\brief Returns the channel's user limit.
	std::optional<int> userLimit() const { return _userLimit; }
	void setUserLimit(int userLimit) { _userLimit = userLimit; }
	QList<QSharedPointer<QDiscordUser>> recipients() const { return _recipients; }
	void setRecipients(QList<QSharedPointer<QDiscordUser>> recipients) { _recipients = recipients; }
	std::optional<QString> icon() const { return _icon; }
	void setIcon(QString icon) { _icon = icon; }
	std::optional<QDiscordID> ownerId() const { return _ownerId; }
	void setOwnerId(QDiscordID ownerId) { _ownerId = ownerId; }
	std::optional<QDiscordID> applicationId() const { return _applicationId; }
	void setApplicationId(QDiscordID applicationId) { _applicationId = applicationId; }
	std::optional<QDiscordID> parentId() const { return _parentId; }
	void setParentId(QDiscordID parentId) { _parentId = parentId; }
	QSharedPointer<QDiscordChannel> parent() const { return _parent; }
	void setParent(QSharedPointer<QDiscordChannel> parent) { _parent = parent; }
	///\brief Returns a pointer to this channel's parent guild.
	QSharedPointer<QDiscordGuild> guild() const { return _guild; }
	/*!
	 * \brief Sets this object's parent guild.
	 * \param guild A pointer to this object's new parent guild.
	 */
	void setGuild(const QSharedPointer<QDiscordGuild>& guild);
	/*!
	 * \brief Returns a pointer to this channel's recipient, if this is a
	 * private channel.
	 */
	///\brief Returns a string which allows you to mention this channel.
	QString mention() const { return QString("<#" + _id.toString() + ">"); }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._type, "type");
		field(a, self._name, "name");
		field(a, self._parentId, "parent_id");
		field(a, self._permission_overwrites, "permission_overwrites");
		field(a, self._nsfw, "_nsfw");
		field(a, self._rate_limit_per_user, "rate_limit_per_user");
		field(a, self._guildId, "guild_id");
		field(a, self._position, "position");
		field(a, self._icon, "icon");
		field(a, self._recipients, "recipients");
		field(a, self._ownerId, "owner_id");
		field(a, self._applicationId, "application_id");
		field(a, self._topic, "topic");
		field(a, self._lastMessageId, "last_message_id");
		field(a, self._bitrate, "bitrate");
		field(a, self._userLimit, "user_limit");
		field(a, self._last_pin_timestamp, "last_pin_timestamp");
		field(a, self._rtc_region, "rtc_region");
		field(a, self._video_quality_mode, "video_quality_mode");
		field(a, self._message_count, "message_count");
		field(a, self._member_count, "member_count");
		field(a, self._thread_metadata, "thread_metadata");
		field(a, self._member, "member");
		field(a, self._default_auto_archive_duration, "default_auto_archive_duration");
		field(a, self._permissions, "permissions");
		field(a, self._flags, "flags");
	}

private:
	QDiscordID                            _id;                            // the id of this channel
	Type                                  _type = Type::UnknownType;      // the type of channel
	std::optional<QDiscordID>             _guildId;                       // the id of the guild (may be missing for some channel objects received over gateway guild dispatches)
	std::optional<int>                    _position;                      // sorting position of the channel
	QList<QDiscordPermissionOverwrite>    _permission_overwrites;         // explicit permission overwrites for membersand roles
	std::optional<QString>                _name;                          // the name of the channel (1-100 characters)
	std::optional<QString>                _topic;                         // the channel topic (0-1024 characters)
	std::optional<bool>                   _nsfw;                          // whether the channel is nsfw
	std::optional<QDiscordID>             _lastMessageId;                 // the id of the last message sent in this channel (or thread for GUILD_FORUM channels) (may not point to an existing or valid message or thread)
	std::optional<int>                    _bitrate;                       // the bitrate (in bits) of the voice channel
	std::optional<int>                    _userLimit;                     // the user limit of the voice channel
	std::optional<int>                    _rate_limit_per_user;           // amount of seconds a user has to wait before sending another message (0-21600); bots, as well as users with the permission manage_messages or manage_channel, are unaffected
	QList<QSharedPointer<QDiscordUser>>   _recipients;                    // the recipients of the DM
	std::optional<QString>                _icon;                          // icon hash of the group DM
	std::optional<QDiscordID>             _ownerId;                       // id of the creator of the group DM or thread
	std::optional<QDiscordID>             _applicationId;                 // application id of the group DM creator if it is bot-created
	std::optional<QDiscordID>             _parentId;                      // for guild channels: id of the parent category for a channel (each parent category can contain up to 50 channels), for threads: id of the text channel this thread was created
	std::optional<QDateTime>              _last_pin_timestamp;            // when the last pinned message was pinned. This may be null in events such as GUILD_CREATE when a message is not pinned.
	std::optional<QString>                _rtc_region;                    // voice region id for the voice channel, automatic when set to null
	std::optional<VideoQualityMode>       _video_quality_mode;            // the camera video quality mode of the voice channel, 1 when not present
	std::optional<int>                    _message_count;                 // an approximate count of messages in a thread, stops counting at 50
	std::optional<int>                    _member_count;                  // an approximate count of users in a thread, stops counting at 50
	std::optional<QDiscordThreadMetadata> _thread_metadata;               // thread-specific fields not needed by other channels
	std::optional<QDiscordThreadMember>   _member;                        // thread member object for the current user, if they have joined the thread, only included on certain API endpoints
	std::optional<int>                    _default_auto_archive_duration; // default duration that the clients (not the API) will use for newly created threads, in minutes, to automatically archive the thread after recent activity, can be set to: 60, 1440, 4320, 10080
	std::optional<QDiscordPermissions>    _permissions;                   // computed permissions for the invoking user in the channel, including overwrites, only included when part of the resolved data received on a slash command interaction
	std::optional<ChannelFlags>           _flags;                         // channel flags combined as a bitfield

	QWeakPointer<QDiscordChannel>         _parent;
	QWeakPointer<QDiscordGuild>           _guild;
};
Q_DECLARE_METATYPE(QDiscordChannel)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordChannel::Type& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordChannel::Type& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordChannel::Type>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordChannel::Type>& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDiscordChannel::VideoQualityMode>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDiscordChannel::VideoQualityMode>& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDiscordChannel::ChannelFlags>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDiscordChannel::ChannelFlags>& value, const QString& name);
} // namespace QDiscordModel

