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
#include "QDiscordMember.h"
#include "QDiscordUser.h"
#include "QDiscordApplication.h"
#include "QDiscordChannel.h"
#include "QDiscordAttachment.h"
#include "QDiscordMessageComponent.h"
#include "QDiscordRole.h"
#include "QDiscordChannelMention.h"
#include "QDiscordEmbed.h"
#include "QDiscordSticker.h"
#include "QDiscordGuild.h"

class QDiscordRest;
class QDiscordInteraction;


class QDiscordMessageActivity
	: public QDiscordModelBase<QDiscordMessageActivity>
{
	Q_GADGET
public:
	enum class Type : qint8
	{
		JOIN         = 1,
		SPECTATE     = 2,
		LISTEN       = 3,
		JOIN_REQUEST = 5,
		Unknown      = -1
	};
	Q_ENUM(Type)

	static QSharedPointer<QDiscordMessageActivity> fromJson(const QJsonObject& object);
	QDiscordMessageActivity(const QJsonObject& object);
	QDiscordMessageActivity() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._type, "type");
		field(a, self._party_id, "party_id");
	}

private:
	Type                   _type = Type::Unknown; // type of message activity
	std::optional<QString> _party_id; // party_id from a Rich Presence event
};
Q_DECLARE_METATYPE(QDiscordMessageActivity)


class QDiscordMessageReference
	: public QDiscordModelBase<QDiscordMessageReference>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordMessageReference> fromJson(const QJsonObject& object);
	QDiscordMessageReference(const QJsonObject& object);
	QDiscordMessageReference() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	const std::optional<QDiscordID>& message_id() const { return _message_id; }
	void setMessage_id(const QDiscordID& id) { _message_id = id; }
	const std::optional<QDiscordID>& channel_id() const { return _channel_id; }
	void setChannel_id(const QDiscordID& id) { _channel_id = id; }
	const std::optional<QDiscordID>& guild_id() const { return _guild_id; }
	void setGuild_id(const QDiscordID& id) { _guild_id = id; }
	const std::optional<bool>& fail_if_not_exists() const { return _fail_if_not_exists; }
	void setFail_if_not_exists(const bool fail_if_not_exists) { _fail_if_not_exists = fail_if_not_exists; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._message_id, "message_id");
		field(a, self._channel_id, "channel_id");
		field(a, self._guild_id, "guild_id");
		field(a, self._fail_if_not_exists, "fail_if_not_exists");
	}

private:
	std::optional<QDiscordID> _message_id;         // id of the originating message
	std::optional<QDiscordID> _channel_id;         // id of the originating message's channel
	std::optional<QDiscordID> _guild_id;           // id of the originating message's guild
	std::optional<bool>       _fail_if_not_exists; // when sending, whether to error if the referenced message doesn't exist instead of sending as a normal (non-reply) message, default true
};
Q_DECLARE_METATYPE(QDiscordMessageReference)


class QDiscordMessage
	: public QDiscordModelBase<QDiscordMessage>
	, public QDiscordModel::CompareById<QDiscordMessage>
{
	Q_GADGET

	Q_PROPERTY(QDiscordID dId READ id WRITE setId)
	Q_PROPERTY(QDiscordID channelId READ channelId WRITE setChannelId)
	Q_PROPERTY(QSharedPointer<QDiscordUser> author READ author WRITE setAuthor)
	Q_PROPERTY(QString content READ content WRITE setContent)
	Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp)
	Q_PROPERTY(std::optional<QDateTime> editedTimestamp READ editedTimestamp WRITE setEditedTimestamp)
	Q_PROPERTY(bool tts READ tts WRITE setTts)
	Q_PROPERTY(bool mentionEveryone READ mentionEveryone WRITE setMentionEveryone)
	Q_PROPERTY(QList<QDiscordUser> mentions READ mentions WRITE setMentions)
	Q_PROPERTY(QDiscordID nonce READ nonce WRITE setNonce)
	Q_PROPERTY(bool pinned READ pinned WRITE setPinned)
	Q_PROPERTY(QSharedPointer<QDiscordChannel> channel READ channel WRITE setChannel)
	Q_PROPERTY(QSharedPointer<QDiscordGuild> guild READ guild STORED false)

public:
	enum class Type : qint8
	{
		DEFAULT                                      = 0,
		RECIPIENT_ADD                                = 1,
		RECIPIENT_REMOVE                             = 2,
		CALL                                         = 3,
		CHANNEL_NAME_CHANGE                          = 4,
		CHANNEL_ICON_CHANGE                          = 5,
		CHANNEL_PINNED_MESSAGE                       = 6,
		GUILD_MEMBER_JOIN                            = 7,
		USER_PREMIUM_GUILD_SUBSCRIPTION              = 8,
		USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1       = 9,
		USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2       = 10,
		USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3       = 11,
		CHANNEL_FOLLOW_ADD                           = 12,
		GUILD_DISCOVERY_DISQUALIFIED                 = 14,
		GUILD_DISCOVERY_REQUALIFIED                  = 15,
		GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING = 16,
		GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING   = 17,
		THREAD_CREATED                               = 18,
		REPLY                                        = 19,
		CHAT_INPUT_COMMAND                           = 20,
		THREAD_STARTER_MESSAGE                       = 21,
		GUILD_INVITE_REMINDER                        = 22,
		CONTEXT_MENU_COMMAND                         = 23
	};
	Q_ENUM(Type)

	enum class MessageFlags : qint16
	{
		CROSSPOSTED                            = 1 << 0, // this message has been published to subscribed channels (via Channel Following)
		IS_CROSSPOST                           = 1 << 1, // this message originated from a message in another channel (via Channel Following)
		SUPPRESS_EMBEDS                        = 1 << 2, // do not include any embeds when serializing this message
		SOURCE_MESSAGE_DELETED                 = 1 << 3, // the source message for this crosspost has been deleted (via Channel Following)
		URGENT                                 = 1 << 4, // this message came from the urgent message system
		HAS_THREAD                             = 1 << 5, // this message has an associated thread, with the same id as the message
		EPHEMERAL                              = 1 << 6, // this message is only visible to the user who invoked the Interaction
		LOADING                                = 1 << 7, // this message is an Interaction Response and the bot is "thinking"
		FAILED_TO_MENTION_SOME_ROLES_IN_THREAD = 1 << 8, // this message failed to mention some roles and add their members to the thread
	};
		
	static QSharedPointer<QDiscordMessage> fromJson(const QJsonObject& object);
	QDiscordMessage(const QJsonObject& object);
	QDiscordMessage() = default;
	QDiscordMessage(const QString& content) : _content(content) {};

	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	static void create(QDiscordRest& rest, const QDiscordID& channelId, const QFileInfo& file, const QJsonObject& data, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback = nullptr);

	void sendCreate(QDiscordRest& rest, const QDiscordID& channelId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback = nullptr);
	void sendEdit(QDiscordRest& rest, const QDiscordID& channelId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback = nullptr);
	static void remove(QDiscordRest& rest, const QDiscordID& channelId, const QDiscordID& messageId, const std::function<void(bool)>& callback = nullptr);
	static void bulkRemove(QDiscordRest& rest, const QDiscordID& channelId, const QList<QDiscordID>& messagesIds, const std::function<void(bool)>& callback = nullptr);
	static void get(QDiscordRest& rest, const QDiscordID& channelId, const QDiscordID& messageId, const std::function<void(QSharedPointer<QDiscordMessage>)>& callback = nullptr);
	static void ack(QDiscordRest& rest, const QDiscordID& channelId, const QDiscordID& messageId, const std::function<void(bool)>& callback = nullptr);
	void sendAck(QDiscordRest& rest, const QDiscordID& channelId, const std::function<void(bool)>& callback = nullptr);

	///\brief Returns the message's ID.
	QDiscordID id() const { return _id; }
	void setId(QDiscordID id) { _id = id; }
	///\brief Returns the ID of the channel this message was sent in.
	QDiscordID channelId() const { return _channel_id; }
	void setChannelId(QDiscordID id) { _channel_id = id; }
	///\brief Returns a pointer to the user that sent this message.
	QSharedPointer<QDiscordUser> author() const { return _author; }
	void setAuthor(QSharedPointer<QDiscordUser> author) { _author = author; }
	///\brief Returns the message's contents.
	QString content() const { return _content; }
	void setContent(const QString& content) { _content = content; }
	///\brief Returns the date at which the message was created.
	QDateTime timestamp() const { return _timestamp; }
	void setTimestamp(const QDateTime& timestamp) { _timestamp = timestamp; }
	std::optional<QDateTime> editedTimestamp() const { return _editedTimestamp; }
	void setEditedTimestamp(const std::optional<QDateTime>& editedTimestamp) { _editedTimestamp = editedTimestamp; }
	void resetEditedTimestamp() { _editedTimestamp.reset(); }
	///\brief Returns whether the message will use text to speech.
	bool tts() const { return _tts; }
	void setTts(bool tts) { _tts = tts; }
	///\brief Returns whether the message successfully mentioned everyone.
	bool mentionEveryone() const { return _mentionEveryone; }
	void setMentionEveryone(bool mentionEveryone) { _mentionEveryone = mentionEveryone; }
	///\brief Returns a list of users mentioned in this message.
	QList<QDiscordUser> mentions() const { return _mentions; }
	void setMentions(QList<QDiscordUser> mentions) { _mentions = mentions; }
	const QList<QSharedPointer<QDiscordAttachment>>& attachments() const { return _attachments; }
	const QList<QByteArray>& attachmentsFiles() const { return _files; }
	void addAttachment(const QSharedPointer<QDiscordAttachment>& attachment, const QByteArray& data) { _attachments.append(attachment); _files.append(data); }
	QDiscordID nonce() const { return _nonce; }
	void setNonce(QDiscordID nonce) { _nonce = nonce; }
	bool pinned() const { return _pinned; }
	void setPinned(bool pinned) { _pinned = pinned; }
	QSharedPointer<QDiscordMessageReference> message_reference() const { return _message_reference; }
	void setMessage_reference(QSharedPointer<QDiscordMessageReference> message_reference) { _message_reference = message_reference; }
	Type type() const { return _type; }
	void setType(Type type) { _type = type; }

	///\brief Returns a pointer to the channel this message was sent in.
	QSharedPointer<QDiscordChannel> channel() const { return _channel; }
	void setChannel(QSharedPointer<QDiscordChannel> channel) { _channel = channel; }
	/*!
	 * \brief Returns a pointer to the guild this message was sent in using
	 * the channel parameter provided in the class' constructor.
	 * \returns `nullptr` if the message was sent in a private channel and thus
	 * the channel has no guild or if a channel was not provided in the class'
	 * constructor.
	 */
	QSharedPointer<QDiscordGuild> guild() const;

	const QList<QSharedPointer<QDiscordMessageComponent>>& components() const { return _components; }
	void clearComponents() { _components.clear(); }
	void addComponent(QSharedPointer<QDiscordMessageComponent> component) { _components.append(component); }
	void setComponents(const QList<QSharedPointer<QDiscordMessageComponent>>& components) { _components = components; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._channel_id, "channel_id");
		field(a, self._guild_id, "guild_id");
		field(a, self._author, "author");
		field(a, self._member, "member");
		field(a, self._content, "content");
		field(a, self._timestamp, "timestamp");
		field(a, self._editedTimestamp, "edited_timestamp");
		field(a, self._tts, "tts");
		field(a, self._mentionEveryone, "mention_everyone");
		field(a, self._nonce, "nonce");
		field(a, self._mentions, "mentions");
		field(a, self._mention_roles, "mention_roles");
		field(a, self._mention_channels, "_mention_channels");
		field(a, self._attachments, "attachments");
		field(a, self._embeds, "embeds");
		field(a, self._reactions, "reactions");
		field(a, self._pinned, "pinned");
		field(a, self._webhook_id, "webhook_id");
		field(a, self._type, "type");
		field(a, self._activity, "activity");
		field(a, self._application, "application");
		field(a, self._application_id, "application_id");
		field(a, self._message_reference, "message_reference");
		field(a, self._flags, "flags");
		field(a, self._referenced_message, "referenced_message");
		field(a, self._interaction, "interaction");
		field(a, self._thread, "thread");
		field(a, self._components, "components");
		field(a, self._sticker_items, "sticker_items");
		field(a, self._stickers, "stickers");
	}

private:
	QDiscordID                                      _id;
	QDiscordID                                      _channel_id;
	std::optional<QDiscordID>                       _guild_id;
	QSharedPointer<QDiscordUser>                    _author;
	std::optional<QDiscordMember>                   _member;
	QString                                         _content;
	QDateTime                                       _timestamp;
	std::optional<QDateTime>                        _editedTimestamp;
	bool                                            _tts = false;
	bool                                            _mentionEveryone = false;
	QList<QDiscordUser>                             _mentions;
	QList<QDiscordRole>                             _mention_roles;
	QList<QDiscordChannelMention>                   _mention_channels;
	QList<QSharedPointer<QDiscordAttachment>>       _attachments;
	QList<QDiscordEmbed>                            _embeds;
	QList<QDiscordReaction>                         _reactions;
	QDiscordID                                      _nonce;
	bool                                            _pinned = false;
	std::optional<QDiscordID>                       _webhook_id;
	Type                                            _type = Type::DEFAULT;
	std::optional<QDiscordMessageActivity>          _activity;
	std::optional<QDiscordApplication>              _application;
	std::optional<QDiscordID>                       _application_id;
	QSharedPointer<QDiscordMessageReference>        _message_reference;
	std::optional<int>                              _flags; // MessageFlags
	QSharedPointer<QDiscordMessage>                 _referenced_message;
	QSharedPointer<QDiscordInteraction>             _interaction;
	std::optional<QDiscordChannel>                  _thread;
	QList<QSharedPointer<QDiscordMessageComponent>> _components;
	QList<QDiscordStickerItem>                      _sticker_items;
	QList<QDiscordSticker>                          _stickers;

	QSharedPointer<QDiscordChannel>                 _channel;
	QList<QByteArray>                               _files;
};
Q_DECLARE_METATYPE(QDiscordMessage)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessage::Type& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessage::Type& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessageActivity::Type& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessageActivity::Type& value, const QString& name);
}; // namespace QDiscordModel

