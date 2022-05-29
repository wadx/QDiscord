
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordApplicationCommand.h"


QSharedPointer<QDiscordApplicationCommandOptionChoice> QDiscordApplicationCommandOptionChoice::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordApplicationCommandOptionChoice> out(new QDiscordApplicationCommandOptionChoice());
	out->deserialize(object);
	return out;
}


QDiscordApplicationCommandOptionChoice::QDiscordApplicationCommandOptionChoice(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordApplicationCommandOptionChoice::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordApplicationCommandOptionChoice::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordApplicationCommandOption> QDiscordApplicationCommandOption::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordApplicationCommandOption> out(new QDiscordApplicationCommandOption());
	out->deserialize(object);
	return out;
}


QDiscordApplicationCommandOption::QDiscordApplicationCommandOption(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordApplicationCommandOption::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordApplicationCommandOption::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordApplicationCommand> QDiscordApplicationCommand::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordApplicationCommand> out(new QDiscordApplicationCommand());
	out->deserialize(object);
	return out;
}


QDiscordApplicationCommand::QDiscordApplicationCommand(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordApplicationCommand::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordApplicationCommand::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordApplicationCommandPermissions> QDiscordApplicationCommandPermissions::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordApplicationCommandPermissions> out(new QDiscordApplicationCommandPermissions());
	out->deserialize(object);
	return out;
}


QDiscordApplicationCommandPermissions::QDiscordApplicationCommandPermissions(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordApplicationCommandPermissions::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordApplicationCommandPermissions::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordGuildApplicationCommandPermissions> QDiscordGuildApplicationCommandPermissions::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordGuildApplicationCommandPermissions> out(new QDiscordGuildApplicationCommandPermissions());
	out->deserialize(object);
	return out;
}


QDiscordGuildApplicationCommandPermissions::QDiscordGuildApplicationCommandPermissions(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordGuildApplicationCommandPermissions::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordGuildApplicationCommandPermissions::serialize() const
{
	return serializeJson();
}


void QDiscordApplicationCommand::sendCreate(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const std::function<void(QSharedPointer<QDiscordApplicationCommand>)>& callback)
{
	AssertErrorRetVoid(!applicationId.isNull(), "QDiscordApplicationCommand::sendCreate() - Application id is zero");
	QJsonObject object = serialize();
	//AssertDumpJsonObject("QDiscordApplicationCommand::sendCreate request", object);
	rest.request(guildId.isNull() ? QDiscordRoutes::ApplicationCommands::createGlobalCommand(applicationId) : QDiscordRoutes::ApplicationCommands::createGuildCommand(applicationId, guildId),
		object, [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(QSharedPointer<QDiscordApplicationCommand>());
				return;
			}
			QJsonObject object = QJsonDocument::fromJson(reply->readAll()).object();
			//AssertDumpJsonObject("QDiscordApplicationCommand::sendCreate reply", object);
			QSharedPointer<QDiscordApplicationCommand> command = QDiscordApplicationCommand::fromJson(object);
			callback(command);
		}
	});
}


void QDiscordApplicationCommand::sendEdit(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const QDiscordID& commandId, const std::function<void(QSharedPointer<QDiscordApplicationCommand>)>& callback)
{
	AssertErrorRetVoid(!applicationId.isNull(), "QDiscordApplicationCommand::sendCreate() - Application id is zero");
	QJsonObject object = serialize();
	//AssertDumpJsonObject("QDiscordApplicationCommand::sendEdit request", object);
	rest.request(guildId.isNull() ? QDiscordRoutes::ApplicationCommands::editGlobalCommand(applicationId, commandId) : QDiscordRoutes::ApplicationCommands::editGuildCommand(applicationId, guildId, commandId),
		object, [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(QSharedPointer<QDiscordApplicationCommand>());
				return;
			}
			QJsonObject object = QJsonDocument::fromJson(reply->readAll()).object();
			//AssertDumpJsonObject("QDiscordApplicationCommand::sendEdit reply", object);
			QSharedPointer<QDiscordApplicationCommand> command = QDiscordApplicationCommand::fromJson(object);
			callback(command);
		}
	});
}


void QDiscordApplicationCommand::sendRemove(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const QDiscordID& commandId, const std::function<void(bool)>& callback)
{
	AssertErrorRetVoid(!applicationId.isNull(), "QDiscordApplicationCommand::sendCreate() - Application id is zero");
	rest.request(guildId.isNull() ? QDiscordRoutes::ApplicationCommands::deleteGlobalCommand(applicationId, commandId) : QDiscordRoutes::ApplicationCommands::deleteGuildCommand(applicationId, guildId, commandId),
		QJsonObject(), [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(false);
				return;
			}
			callback(true);
		}
	});
}


void QDiscordApplicationCommand::requestList(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const std::function<void(QList<QSharedPointer<QDiscordApplicationCommand>>&)>& callback)
{
	AssertErrorRetVoid(!applicationId.isNull(), "QDiscordApplicationCommand::sendCreate() - Application id is zero");
	rest.request(guildId.isNull() ? QDiscordRoutes::ApplicationCommands::getGlobalCommands(applicationId) : QDiscordRoutes::ApplicationCommands::getGuildCommands(applicationId, guildId),
	QJsonObject(), [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			QList<QSharedPointer<QDiscordApplicationCommand>> commands;
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(commands);
				return;
			}
			QJsonArray array = QJsonDocument::fromJson(reply->readAll()).array();
			for (const QJsonValueRef& item : array)
			{
				QJsonObject object = item.toObject();
				//AssertDumpJsonObject("QDiscordApplicationCommand::requestList reply", object);
				QSharedPointer<QDiscordApplicationCommand> command = QDiscordApplicationCommand::fromJson(object);
				commands.append(command);
			}
			callback(commands);
		}
	});
}


void QDiscordGuildApplicationCommandPermissions::request(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const QDiscordID& commandId, const std::function<void(QSharedPointer<QDiscordGuildApplicationCommandPermissions>)>& callback)
{
	AssertErrorRetVoid(!applicationId.isNull(), "QDiscordGuildApplicationCommandPermissions::request() - Application id is zero");
	AssertErrorRetVoid(!guildId.isNull(), "QDiscordGuildApplicationCommandPermissions::request() - Guild id is zero");
	AssertErrorRetVoid(!commandId.isNull(), "QDiscordGuildApplicationCommandPermissions::request() - Command id is zero");
	rest.request(QDiscordRoutes::ApplicationCommands::getGuildCommandPermissions(applicationId, guildId, commandId),
	QJsonObject(), [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(QSharedPointer<QDiscordGuildApplicationCommandPermissions>());
				return;
			}
			QJsonObject object = QJsonDocument::fromJson(reply->readAll()).object();
			QSharedPointer<QDiscordGuildApplicationCommandPermissions> permissions = QDiscordGuildApplicationCommandPermissions::fromJson(object);
			callback(permissions);
		}
	});
}


void QDiscordGuildApplicationCommandPermissions::requestList(QDiscordRest& rest, const QDiscordID& applicationId, const QDiscordID& guildId, const std::function<void(QList<QSharedPointer<QDiscordGuildApplicationCommandPermissions>>&)>& callback)
{
	AssertErrorRetVoid(!applicationId.isNull(), "QDiscordGuildApplicationCommandPermissions::requestList() - Application id is zero");
	AssertErrorRetVoid(!guildId.isNull(), "QDiscordGuildApplicationCommandPermissions::requestList() - Guild id is zero");
	rest.request(QDiscordRoutes::ApplicationCommands::getGuildCommandsPermissions(applicationId, guildId),
	QJsonObject(), [callback](QNetworkReply* reply)
	{
		if (callback)
		{
			QList<QSharedPointer<QDiscordGuildApplicationCommandPermissions>> permissionsList;
			if (reply->error() != QNetworkReply::NoError)
			{
				callback(permissionsList);
				return;
			}
			QJsonArray array = QJsonDocument::fromJson(reply->readAll()).array();
			for (const QJsonValueRef& item : array)
			{
				QJsonObject object = item.toObject();
				QSharedPointer<QDiscordGuildApplicationCommandPermissions> permissions = QDiscordGuildApplicationCommandPermissions::fromJson(object);
				permissionsList.append(permissions);
			}
			callback(permissionsList);
		}
	});
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, ApplicationCommandType& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = ApplicationCommandType::CHAT_INPUT;
		break;
	case 2:
		value = ApplicationCommandType::USER;
		break;
	case 3:
		value = ApplicationCommandType::MESSAGE;
		break;
	default:
		value = ApplicationCommandType::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const ApplicationCommandType& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, ApplicationCommandOptionType& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = ApplicationCommandOptionType::SUB_COMMAND;
		break;
	case 2:
		value = ApplicationCommandOptionType::SUB_COMMAND_GROUP;
		break;
	case 3:
		value = ApplicationCommandOptionType::STRING;
		break;
	case 4:
		value = ApplicationCommandOptionType::INTEGER;
		break;
	case 5:
		value = ApplicationCommandOptionType::BOOLEAN;
		break;
	case 6:
		value = ApplicationCommandOptionType::USER;
		break;
	case 7:
		value = ApplicationCommandOptionType::CHANNEL;
		break;
	case 8:
		value = ApplicationCommandOptionType::ROLE;
		break;
	case 9:
		value = ApplicationCommandOptionType::MENTIONABLE;
		break;
	case 10:
		value = ApplicationCommandOptionType::NUMBER;
		break;
	case 11:
		value = ApplicationCommandOptionType::ATTACHMENT;
		break;
	default:
		value = ApplicationCommandOptionType::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const ApplicationCommandOptionType& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordApplicationCommandPermissions::Type& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordApplicationCommandPermissions::Type::ROLE;
		break;
	case 2:
		value = QDiscordApplicationCommandPermissions::Type::USER;
		break;
	case 3:
		value = QDiscordApplicationCommandPermissions::Type::CHANNEL;
		break;
	default:
		value = QDiscordApplicationCommandPermissions::Type::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordApplicationCommandPermissions::Type& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


