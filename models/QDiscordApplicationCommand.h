
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordChannel.h"


enum class ApplicationCommandType : qint8
{
	CHAT_INPUT = 1, // Slash commands; a text - based command that shows up when a user types /
	USER       = 2, // A UI - based command that shows up when you right click or tap on a user
	MESSAGE    = 3, // A UI - based command that shows up when you right click or tap on a message
	Unknown    = -1
};


enum class ApplicationCommandOptionType : qint8
{
	SUB_COMMAND       = 1,
	SUB_COMMAND_GROUP = 2,
	STRING            = 3,
	INTEGER           = 4, // Any integer between - 2 ^ 53 and 2 ^ 53
	BOOLEAN           = 5,
	USER              = 6,
	CHANNEL           = 7, // Includes all channel types + categories
	ROLE              = 8,
	MENTIONABLE       = 9, // Includes users and roles
	NUMBER            = 10, // Any double between - 2 ^ 53 and 2 ^ 53
	ATTACHMENT        = 11, // attachment object
	Unknown           = -1
};


class QDiscordApplicationCommandOptionChoice
	: public QDiscordModelBase<QDiscordApplicationCommandOptionChoice>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordApplicationCommandOptionChoice> fromJson(const QJsonObject& object);
	QDiscordApplicationCommandOptionChoice(const QJsonObject& object);
	QDiscordApplicationCommandOptionChoice() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._name_localizations, "name_localizations");
		field(a, self._value, "value");
	}

private:
	QString                            _name; // 1-100 character choice name
	QMap<QString, QString>             _name_localizations; // dictionary with keys in available locales. Localization dictionary for the name field. Values follow the same restrictions as name
	std::variant<QString, int, double> _value; // value of the choice, up to 100 characters if string
};
Q_DECLARE_METATYPE(QDiscordApplicationCommandOptionChoice)


class QDiscordApplicationCommandOption
	: public QDiscordModelBase<QDiscordApplicationCommandOption>
{
	Q_GADGET
public:
	Q_ENUM(ApplicationCommandOptionType)
	
	static QSharedPointer<QDiscordApplicationCommandOption> fromJson(const QJsonObject& object);
	QDiscordApplicationCommandOption(const QJsonObject& object);
	QDiscordApplicationCommandOption() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	const ApplicationCommandOptionType type() const { return _type; }
	void setType(const ApplicationCommandOptionType type) { _type = type; }
	const QString& name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	const QString& description() const { return _description; }
	void setDescription(const QString& description) { _description = description; }
	const std::optional<bool>& required() const { return _required; }
	void setRequired(const bool required) { _required = required; }
	const QList<QSharedPointer<QDiscordApplicationCommandOption>>& options() const { return _options; }
	void addOption(QSharedPointer<QDiscordApplicationCommandOption> option) { _options.append(option); }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._type, "type");
		field(a, self._name, "name");
		field(a, self._name_localizations, "name_localizations");
		field(a, self._description, "description");
		field(a, self._description_localizations, "description_localizations");
		field(a, self._required, "required");
		field(a, self._choices, "choices");
		field(a, self._options, "options");
		field(a, self._channel_types, "channel_types");
		field(a, self._min_value, "min_value");
		field(a, self._max_value, "max_value");
		field(a, self._autocomplete, "autocomplete");
	}

private:
	ApplicationCommandOptionType                            _type = ApplicationCommandOptionType::Unknown; // the type of option
	QString                                                 _name;                      // 1-32 character name
	QMap<QString, QString>                                  _name_localizations;        // Localization dictionary for the name field. Values follow the same restrictions as name
	QString                                                 _description;               // 1-100 character description
	QMap<QString, QString>                                  _description_localizations; // Localization dictionary for the description field. Values follow the same restrictions as description
	std::optional<bool>                                     _required;                  // if the parameter is required or optional--default false
	QList<QDiscordApplicationCommandOptionChoice>           _choices;                   // choices for STRING, INTEGER, and NUMBER types for the user to pick from, max 25
	QList<QSharedPointer<QDiscordApplicationCommandOption>> _options;                   // if the option is a subcommand or subcommand group type, these nested options will be the parameters
	QList<QDiscordChannel::Type>                            _channel_types;             // if the option is a channel type, the channels shown will be restricted to these types
	std::optional<double>                                   _min_value;                 // for INTEGER options, double for NUMBER options  if the option is an INTEGER or NUMBER type, the minimum value permitted
	std::optional<double>                                   _max_value;                 // for INTEGER options, double for NUMBER options  if the option is an INTEGER or NUMBER type, the maximum value permitted
	std::optional<bool>                                     _autocomplete;              // if autocomplete interactions are enabled for this STRING, INTEGER, or NUMBER type option
};
Q_DECLARE_METATYPE(QDiscordApplicationCommandOption)


class QDiscordApplicationCommand
	: public QDiscordModelBase<QDiscordApplicationCommand>
{
	Q_GADGET
public:
	Q_ENUM(ApplicationCommandType)

	static QSharedPointer<QDiscordApplicationCommand> fromJson(const QJsonObject& object);
	QDiscordApplicationCommand(const QJsonObject& object);
	QDiscordApplicationCommand() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	void sendCreate(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const std::function<void(QSharedPointer<QDiscordApplicationCommand>)>& callback = nullptr);
	void sendEdit(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const QDiscordID& commandId, const std::function<void(QSharedPointer<QDiscordApplicationCommand>)>& callback = nullptr);
	static void sendRemove(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const QDiscordID& commandId, const std::function<void(bool)>& callback = nullptr);
	static void requestList(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const std::function<void(QList<QSharedPointer<QDiscordApplicationCommand>>&)>& callback);

	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	const ApplicationCommandType type() const { return _type; }
	void setType(const ApplicationCommandType type) { _type = type; }
	const QDiscordID& applicationId() const { return _application_id; }
	void setApplicationId(const QDiscordID& applicationId) { _application_id = applicationId; }
	const std::optional<QDiscordID>& guild_id() const { return _guild_id; }
	void setGuildId(const QDiscordID& guild_id) { _guild_id = guild_id; }
	const QString& name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	const QString& description() const { return _description; }
	void setDescription(const QString& description) { _description = description; }
	const QMap<QString, QString>& description_localizations() const { return _description_localizations; }
	void addDescription_localization(const QString& lang, const QString& value) { _description_localizations.insert(lang, value); }
	const QList<QSharedPointer<QDiscordApplicationCommandOption>>& options() const { return _options; }
	void addOption(QSharedPointer<QDiscordApplicationCommandOption> option) { _options.append(option); }
	const QDiscordID& version() const { return _version; }
	void setVersion(const QDiscordID& version) { _version = version; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._type, "type");
		field(a, self._application_id, "application_id");
		field(a, self._guild_id, "guild_id");
		field(a, self._name, "name");
		field(a, self._name_localizations, "name_localizations");
		field(a, self._description, "description");
		field(a, self._description_localizations, "description_localizations");
		field(a, self._options, "options");
		field(a, self._default_member_permissions, "default_member_permissions");
		field(a, self._dm_permission, "dm_permission");
		field(a, self._default_permission, "default_permission");
		field(a, self._version, "version");
	}

private:
	QDiscordID                                              _id;                         // unique id of the command
	ApplicationCommandType                                  _type = ApplicationCommandType::CHAT_INPUT; // the type of command, defaults 1 if not set
	QDiscordID                                              _application_id;             // unique id of the parent application
	std::optional<QDiscordID>                               _guild_id;                   // guild id of the command, if not global
	QString                                                 _name;                       // the name of the invoked command (interaction type:Application Command)
	QMap<QString, QString>                                  _name_localizations;         // Localization dictionary for the name field. Values follow the same restrictions as name
	QString                                                 _description;                // 1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE
	QMap<QString, QString>                                  _description_localizations;  // Localization dictionary for the description field. Values follow the same restrictions as description
	QList<QSharedPointer<QDiscordApplicationCommandOption>> _options;                    // the parameters for the command, max 25 (only for CHAT_INPUT)
	std::optional<QDiscordPermissions>                      _default_member_permissions; // Set of permissions represented as a bit set
	std::optional<bool>                                     _dm_permission;              // Indicates whether the command is available in DMs with the app, only for globally-scoped commands. By default, commands are visible.
	std::optional<bool>                                     _default_permission;         // whether the command is enabled by default when the app is added to a guild (default true)
	QDiscordID                                              _version;                    // autoincrementing version identifier updated during substantial record changes
};
Q_DECLARE_METATYPE(QDiscordApplicationCommand)


class QDiscordApplicationCommandPermissions
	: public QDiscordModelBase<QDiscordApplicationCommandPermissions>
{
	Q_GADGET
public:
	enum class Type : qint8
	{
		ROLE    = 1,
		USER    = 2,
		CHANNEL = 3,
		Unknown = -1
	};
	Q_ENUM(Type)

	static QSharedPointer<QDiscordApplicationCommandPermissions> fromJson(const QJsonObject& object);
	QDiscordApplicationCommandPermissions(const QJsonObject& object);
	QDiscordApplicationCommandPermissions() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	const Type type() const { return _type; }
	void setType(const Type type) { _type = type; }
	const bool permission() const { return _permission; }
	void set_permission(const bool permission) { _permission = permission; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._type, "type");
		field(a, self._permission, "permission");
	}

private:
	QDiscordID _id;         // ID of the role, user, or channel. It can also be a permission constant
	Type       _type;       // application command permission type	role (1), user (2), or channel (3)
	bool       _permission; // true to allow, false, to disallow
};
Q_DECLARE_METATYPE(QDiscordApplicationCommandPermissions)


class QDiscordGuildApplicationCommandPermissions
	: public QDiscordModelBase<QDiscordGuildApplicationCommandPermissions>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordGuildApplicationCommandPermissions> fromJson(const QJsonObject& object);
	QDiscordGuildApplicationCommandPermissions(const QJsonObject& object);
	QDiscordGuildApplicationCommandPermissions() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	static void request(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const QDiscordID& commandId, const std::function<void(QSharedPointer<QDiscordGuildApplicationCommandPermissions>)>& callback);
	static void requestList(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const std::function<void(QList<QSharedPointer<QDiscordGuildApplicationCommandPermissions>>&)>& callback);

	const QDiscordID& id() const { return _id; }
	void setId(const QDiscordID& id) { _id = id; }
	const QDiscordID& application_id() const { return _application_id; }
	void set_application_id(const QDiscordID& id) { _application_id = id; }
	const QDiscordID& guild_id() const { return _guild_id; }
	void set_guild_id(const QDiscordID& id) { _guild_id = id; }
	const QList<QSharedPointer<QDiscordApplicationCommandPermissions>>& permissions() const { return _permissions; }
	void add_permission(const QSharedPointer<QDiscordApplicationCommandPermissions>& permission) { _permissions.append(permission); }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._application_id, "application_id");
		field(a, self._guild_id, "guild_id");
		field(a, self._permissions, "permissions");
	}

private:
	QDiscordID                                                   _id;             // ID of the command
	QDiscordID                                                   _application_id; // ID of the application the command belongs to
	QDiscordID                                                   _guild_id;       // ID of the guild
	QList<QSharedPointer<QDiscordApplicationCommandPermissions>> _permissions;    // Permissions for the command in the guild, max of 100
};
Q_DECLARE_METATYPE(QDiscordGuildApplicationCommandPermissions)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, ApplicationCommandType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const ApplicationCommandType& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, ApplicationCommandOptionType& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const ApplicationCommandOptionType& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordApplicationCommandPermissions::Type& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordApplicationCommandPermissions::Type& value, const QString& name);
} // namespace QDiscordModel


