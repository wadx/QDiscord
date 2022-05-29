
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordChannel.h"
#include "QDiscordMember.h"
#include "QDiscordUser.h"
#include "QDiscordRole.h"
#include "QDiscordMessage.h"
#include "QDiscordAttachment.h"
#include "QDiscordMessageComponent.h" // ComponentType
#include "QDiscordEmoji.h"
#include "QDiscordEmbed.h"
#include "QDiscordApplicationCommand.h"


class QDiscordResolvedData
	: public QDiscordModelBase<QDiscordResolvedData>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordResolvedData> fromJson(const QJsonObject& object);
	QDiscordResolvedData(const QJsonObject& object);
	QDiscordResolvedData() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QDiscordMapIdToObject<QSharedPointer<QDiscordUser>>& users() const { return _users; }
	const QDiscordMapIdToObject<QSharedPointer<QDiscordMember>>& members() const { return _members; }
	const QDiscordMapIdToObject<QSharedPointer<QDiscordRole>>& roles() const { return _roles; }
	const QDiscordMapIdToObject<QSharedPointer<QDiscordChannel>>& channels() const { return _channels; }
	const QDiscordMapIdToObject<QSharedPointer<QDiscordMessage>>& messages() const { return _messages; }
	const QDiscordMapIdToObject<QSharedPointer<QDiscordAttachment>>& attachments() const { return _attachments; }

	template<class Action>
	void map(Action & a)
	{
		using namespace QDiscordModel;
		field(a, _users, "users");
		field(a, _members, "members");
		field(a, _roles, "roles");
		field(a, _channels, "channels");
		field(a, _messages, "messages");
		field(a, _attachments, "attachments");
	}

	template<class Action>
	void map(Action & a) const
	{
		using namespace QDiscordModel;
		field(a, _users, "users");
		field(a, _members, "members");
		field(a, _roles, "roles");
		field(a, _channels, "channels");
		field(a, _messages, "messages");
		field(a, _attachments, "attachments");
	}

private:
	QDiscordMapIdToObject<QSharedPointer<QDiscordUser>>       _users;       // Map of Snowflakes to user objects. the ids and User objects
	QDiscordMapIdToObject<QSharedPointer<QDiscordMember>>     _members;     // Map of Snowflakes to partial member objects. the ids and partial Member objects
	QDiscordMapIdToObject<QSharedPointer<QDiscordRole>>       _roles;       // Map of Snowflakes to role objects. the ids and Role objects
	QDiscordMapIdToObject<QSharedPointer<QDiscordChannel>>    _channels;    // Map of Snowflakes to partial channel objects. the ids and partial Channel objects
	QDiscordMapIdToObject<QSharedPointer<QDiscordMessage>>    _messages;    // Map of Snowflakes to partial messages objects. the ids and partial Message objects
	QDiscordMapIdToObject<QSharedPointer<QDiscordAttachment>> _attachments; // Map of Snowflakes to attachment objects. the ids and attachment objects
};
Q_DECLARE_METATYPE(QDiscordResolvedData)



class QDiscordApplicationCommandInteractionDataOption
	: public QDiscordModelBase<QDiscordApplicationCommandInteractionDataOption>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordApplicationCommandInteractionDataOption> fromJson(const QJsonObject& object);
	QDiscordApplicationCommandInteractionDataOption(const QJsonObject& object);
	QDiscordApplicationCommandInteractionDataOption() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QString& name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	const ApplicationCommandOptionType type() const { return _type; }
	void setType(const ApplicationCommandOptionType type) { _type = type; }
	const std::optional<std::variant<QString, int, double>>& value() const { return _value; }
	void setValue(const std::variant<QString, int, double>& value) { _value = value; }
	const QList<QSharedPointer<QDiscordApplicationCommandInteractionDataOption>>& options() const { return _options; }
	void addOption(QSharedPointer<QDiscordApplicationCommandInteractionDataOption> option) { _options.append(option); }

	template<class Action>
	void map(Action & a)
	{
		using namespace QDiscordModel;
		field(a, _name, "name");
		field(a, _type, "type");
		field(a, _value, "value");
		field(a, _options, "options");
		field(a, _focused, "focused");
	}

	template<class Action>
	void map(Action & a) const
	{
		using namespace QDiscordModel;
		field(a, _name, "name");
		field(a, _type, "type");
		field(a, _value, "value");
		field(a, _options, "options");
		field(a, _focused, "focused");
	}

private:
	QString                                                                _name;    // the name of the parameter
	ApplicationCommandOptionType                                           _type = ApplicationCommandOptionType::Unknown; // value of application command option type
	std::optional<std::variant<QString, int, double>>                      _value;   // the value of the option resulting from user input
	QList<QSharedPointer<QDiscordApplicationCommandInteractionDataOption>> _options; // present if this option is a group or subcommand
	std::optional<bool>                                                    _focused; // true if this option is the currently focused option for autocomplete
};
Q_DECLARE_METATYPE(QDiscordApplicationCommandInteractionDataOption)


class QDiscordSelectOption
	: public QDiscordModelBase<QDiscordSelectOption>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordSelectOption> fromJson(const QJsonObject& object);
	QDiscordSelectOption(const QJsonObject& object);
	QDiscordSelectOption() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<class Action>
	void map(Action & a)
	{
		using namespace QDiscordModel;
		field(a, _label, "label");
		field(a, _value, "value");
		field(a, _description, "description");
		field(a, _emoji, "emoji");
		field(a, _default, "default");
	}

	template<class Action>
	void map(Action & a) const
	{
		using namespace QDiscordModel;
		field(a, _label, "label");
		field(a, _value, "value");
		field(a, _description, "description");
		field(a, _emoji, "emoji");
		field(a, _default, "default");
	}

private:
	QString                      _label;       // the user-facing name of the option, max 100 characters
	QString                      _value;       // the dev-defined value of the option, max 100 characters
	std::optional<QString>       _description; // an additional description of the option, max 100 characters
	std::optional<QDiscordEmoji> _emoji;       // partial emoji object: id, name, and animated
	std::optional<bool>          _default;     // will render this option as selected by default
};
Q_DECLARE_METATYPE(QDiscordSelectOption)


class QDiscordInteractionData
	: public QDiscordModelBase<QDiscordInteractionData>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordInteractionData> fromJson(const QJsonObject& object);
	QDiscordInteractionData(const QJsonObject& object);
	QDiscordInteractionData() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	const QString& name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	const ApplicationCommandType type() const { return _type; }
	void setType(const ApplicationCommandType type) { _type = type; }
	const std::optional<QDiscordResolvedData>& resolved() const { return _resolved; }
	void setResolved(const QDiscordResolvedData& resolved) { _resolved = resolved; }
	const QList<QSharedPointer<QDiscordApplicationCommandInteractionDataOption>>& options() const { return _options; }
	void addOption(QSharedPointer<QDiscordApplicationCommandInteractionDataOption> option) { _options.append(option); }
	const std::optional<QString>& custom_id() const { return _custom_id; }
	void setCustom_id(const QString& custom_id) { _custom_id = custom_id; }
	const std::optional<MessageComponentType>& component_type() const { return _component_type; }
	void setComponent_type(const MessageComponentType component_type) { _component_type = component_type; }
	const QList<QDiscordSelectOption>& values() const { return _values; }
	void setValues(const QList<QDiscordSelectOption>& values) { _values = values; }
	const std::optional<QDiscordID>& target_id() const { return _target_id; }
	void setTarget_id(const QDiscordID& target_id) { _target_id = target_id; }
	const QList<QSharedPointer<QDiscordMessageComponent>>& components() const { return _components; }
	void setComponents(const QList<QSharedPointer<QDiscordMessageComponent>>& components) { _components = components; }

	template<class Action>
	void map(Action & a)
	{
		using namespace QDiscordModel;
		field(a, _id, "id");
		field(a, _name, "name");
		field(a, _type, "type");
		field(a, _resolved, "resolved");
		field(a, _options, "options");
		field(a, _custom_id, "custom_id");
		field(a, _component_type, "component_type");
		field(a, _values, "values");
		field(a, _target_id, "target_id");
		field(a, _components, "components");
	}

	template<class Action>
	void map(Action & a) const
	{
		using namespace QDiscordModel;
		field(a, _id, "id");
		field(a, _name, "name");
		field(a, _type, "type");
		field(a, _resolved, "resolved");
		field(a, _options, "options");
		field(a, _custom_id, "custom_id");
		field(a, _component_type, "component_type");
		field(a, _values, "values");
		field(a, _target_id, "target_id");
		field(a, _components, "components");
	}

private:
	QDiscordID                                                             _id;             // the ID of the invoked command (interaction type:Application Command)
	QString                                                                _name;           // the name of the invoked command (interaction type:Application Command)
	ApplicationCommandType                                                 _type = ApplicationCommandType::Unknown; // the type of the invoked command (interaction type:Application Command)
	std::optional<QDiscordResolvedData>                                    _resolved;       // converted users + roles + channels + attachments (interaction type:Application Command)
	QList<QSharedPointer<QDiscordApplicationCommandInteractionDataOption>> _options;        // the params + values from the user (interaction type:Application Command)
	std::optional<QString>                                                 _custom_id;      // the custom_id of the component (interaction type:Component, Modal Submit)
	std::optional<MessageComponentType>                                    _component_type; // the type of the component (interaction type:Component)
	QList<QDiscordSelectOption>                                            _values;         // the values the user selected	(interaction type:Component (Select))
	std::optional<QDiscordID>                                              _target_id;      // id the of user or message targeted by a user or message command (interaction type:User Command, Message Command)
	QList<QSharedPointer<QDiscordMessageComponent>>                        _components;     // the values submitted by the user (interaction type:Modal Submit)
};
Q_DECLARE_METATYPE(QDiscordInteractionData)


class QDiscordInteraction
	: public QDiscordModelBase<QDiscordInteraction>
{
	Q_GADGET
public:
	enum class InteractionType : qint8
	{
		PING                             = 1,
		APPLICATION_COMMAND              = 2,
		MESSAGE_COMPONENT                = 3,
		APPLICATION_COMMAND_AUTOCOMPLETE = 4,
		MODAL_SUBMIT                     = 5,
		Unknown                          = -1
	};
	Q_ENUM(InteractionType)

	static QSharedPointer<QDiscordInteraction> fromJson(const QJsonObject& object);
	QDiscordInteraction(const QJsonObject& object);
	QDiscordInteraction() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	const QDiscordID& application_id() const { return _application_id; }
	void setApplication_id(const QDiscordID& id) { _application_id = id; }
	const InteractionType type() const { return _type; }
	void setType(const InteractionType type) { _type = type; }
	const QSharedPointer<QDiscordInteractionData> data() const { return _data; }
	void setData(QSharedPointer<QDiscordInteractionData> data) { _data = data; }
	const std::optional<QDiscordID>& guild_id() const { return _guild_id; }
	void setGuild_id(const QDiscordID& guild_id) { _guild_id = guild_id; }
	const std::optional<QDiscordID>& channel_id() const { return _channel_id; }
	void setChannel_id(const QDiscordID& channel_id) { _channel_id = channel_id; }
	const QSharedPointer<QDiscordMember>& member() const { return _member; }
	void setMember(const QSharedPointer<QDiscordMember>& member) { _member = member; }
	const QSharedPointer<QDiscordUser>& user() const { return _user; }
	void setUser(const QSharedPointer<QDiscordUser>& user) { _user = user; }
	const QString& token() const { return _token; }
	void setToken(const QString& token) { _token = token; }
	const int version() const { return _version; }
	void setVersion(const int version) { _version = version; }
	const QSharedPointer<QDiscordMessage>& message() const { return _message; }
	void setMessage(const QSharedPointer<QDiscordMessage>& message) { _message = message; }
	const std::optional<QString>& locale() const { return _locale; }
	void setLocale(const QString& locale) { _locale = locale; }
	const std::optional<QString>& guild_locale() const { return _guild_locale; }
	void setGuild_locale(const QString& guild_locale) { _guild_locale = guild_locale; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._application_id, "application_id");
		field(a, self._type, "type");
		field(a, self._data, "data");
		field(a, self._guild_id, "guild_id");
		field(a, self._channel_id, "channel_id");
		field(a, self._member, "member");
		field(a, self._user, "user");
		field(a, self._token, "token");
		field(a, self._version, "version");
		field(a, self._message, "message");
		field(a, self._locale, "locale");
		field(a, self._guild_locale, "guild_locale");
	}

private:
	QDiscordID                              _id;             // id of the interaction
	QDiscordID                              _application_id; // id of the application this interaction is for
	InteractionType                         _type = InteractionType::Unknown;
	QSharedPointer<QDiscordInteractionData> _data;           // the command data payload
	std::optional<QDiscordID>               _guild_id;       // the guild it was sent from
	std::optional<QDiscordID>               _channel_id;     // the channel it was sent from
	QSharedPointer<QDiscordMember>          _member;         // guild member data for the invoking user, including permissions
	QSharedPointer<QDiscordUser>            _user;           // user object for the invoking user, if invoked in a DM
	QString                                 _token;          // a continuation token for responding to the interaction
	int                                     _version = 1;    // read-only property, always 1
	QSharedPointer<QDiscordMessage>         _message;        // for components, the message they were attached to
	std::optional<QString>                  _locale;         // the selected language of the invoking user
	std::optional<QString>                  _guild_locale;   // the guild's preferred locale, if invoked in a guild
};
Q_DECLARE_METATYPE(QDiscordInteraction)


class QDiscordInteractionCallbackData
	: public QDiscordModelBase<QDiscordInteractionCallbackData>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordInteractionCallbackData> fromJson(const QJsonObject& object);
	QDiscordInteractionCallbackData(const QJsonObject& object);
	QDiscordInteractionCallbackData() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const std::optional<QString>& content() const { return _content; }
	void setContent(const QString& content) { _content = content; }
	const std::optional<int>& flags() const { return _flags; }
	void setFlags(int flags) { _flags = flags; }
	const QList<QSharedPointer<QDiscordMessageComponent>>& components() const { return _components; }
	void clearComponents() { _components.clear(); }
	void addComponent(QSharedPointer<QDiscordMessageComponent> component) { _components.append(component); }
	void setComponents(const QList<QSharedPointer<QDiscordMessageComponent>>& components) { _components = components; }

	const std::optional<QString>& customId() const { return _custom_id; }
	void setCustomId(const QString& custom_id) { _custom_id = custom_id; }
	const std::optional<QString>& title() const { return _title; }
	void setTitle(const QString& title) { _title = title; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._tts, "tts");
		field(a, self._content, "content");
		field(a, self._embeds, "embeds");
		field(a, self._allowed_mentions, "allowed_mentions");
		field(a, self._flags, "flags");
		field(a, self._components, "components");
		field(a, self._attachments, "attachments");
		field(a, self._choices, "choices");
		field(a, self._custom_id, "custom_id");
		field(a, self._title, "title");
	}

private:
	std::optional<bool>                             _tts;              // is the response TTS
	std::optional<QString>                          _content;          // message content
	QList<QDiscordEmbed>                            _embeds;           // array of embeds, supports up to 10 embeds
	QSharedPointer<QDiscordAllowedMentions>         _allowed_mentions; // allowed mentions object
	std::optional<int>                              _flags;            // message flags combined as a bitfield (only SUPPRESS_EMBEDS and EPHEMERAL can be set) QDiscordMessage::MessageFlags
	QList<QSharedPointer<QDiscordMessageComponent>> _components;       // message components
	QList<QDiscordAttachment>                       _attachments;      // array of partial attachment objects, attachment objects with filename and description
	QList<QDiscordApplicationCommandOptionChoice>   _choices;          // autocomplete choices (max of 25 choices)
	std::optional<QString>                          _custom_id;        // a developer-defined identifier for the component, max 100 characters, for Modal
	std::optional<QString>                          _title;            // the title of the popup modal, max 45 characters, for Modal
};
Q_DECLARE_METATYPE(QDiscordInteractionCallbackData)


class QDiscordInteractionResponse
	: public QDiscordModelBase<QDiscordInteractionResponse>
{
	Q_GADGET
public:
	enum class InteractionCallbackType : qint8
	{
		PONG                                    = 1, // ACK a Ping
		CHANNEL_MESSAGE_WITH_SOURCE             = 4, // respond to an interaction with a message
		DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE    = 5, // ACK an interaction and edit a response later, the user sees a loading state
		DEFERRED_UPDATE_MESSAGE                 = 6, // for components, ACK an interactionand edit the original message later; the user does not see a loading state
		UPDATE_MESSAGE                          = 7, // for components, edit the message the component was attached to
		APPLICATION_COMMAND_AUTOCOMPLETE_RESULT = 8, // respond to an autocomplete interaction with suggested choices
		MODAL                                   = 9, // respond to an interaction with a popup modal
		Unknown                                 = -1
	};
	Q_ENUM(InteractionCallbackType)

	static QSharedPointer<QDiscordInteractionResponse> fromJson(const QJsonObject& object);
	QDiscordInteractionResponse(const QJsonObject& object);
	QDiscordInteractionResponse() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	const InteractionCallbackType type() const { return _type; }
	void setType(const InteractionCallbackType type) { _type = type; }
	const QSharedPointer<QDiscordInteractionCallbackData> data() const { return _data; }
	void setData(QSharedPointer<QDiscordInteractionCallbackData> data) { _data = data; }

	void send(QDiscordRest& rest, const QDiscordID& interaction_id, const QString& interaction_token);

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._type, "type");
		field(a, self._data, "data");
	}

private:
	InteractionCallbackType                         _type = InteractionCallbackType::Unknown;
	QSharedPointer<QDiscordInteractionCallbackData> _data;
};
Q_DECLARE_METATYPE(QDiscordInteractionResponse)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordInteraction::InteractionType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordInteraction::InteractionType& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<MessageComponentType>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<MessageComponentType>& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordInteractionResponse::InteractionCallbackType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordInteractionResponse::InteractionCallbackType& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QMap<QString, QString>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QMap<QString, QString>& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::variant<QString, int, double>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::variant<QString, int, double>& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<std::variant<QString, int, double>>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<std::variant<QString, int, double>>& value, const QString& name);
} // namespace QDiscordModel

