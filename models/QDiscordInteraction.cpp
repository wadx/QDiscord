
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordInteraction.h"
#include "QDiscordRoute.h"
#include "QDiscordRest.h"


QSharedPointer<QDiscordResolvedData> QDiscordResolvedData::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordResolvedData> out(new QDiscordResolvedData());
	out->deserialize(object);
	return out;
}


QDiscordResolvedData::QDiscordResolvedData(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordResolvedData::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordResolvedData::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordApplicationCommandInteractionDataOption> QDiscordApplicationCommandInteractionDataOption::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordApplicationCommandInteractionDataOption> out(new QDiscordApplicationCommandInteractionDataOption());
	out->deserialize(object);
	return out;
}


QDiscordApplicationCommandInteractionDataOption::QDiscordApplicationCommandInteractionDataOption(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordApplicationCommandInteractionDataOption::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordApplicationCommandInteractionDataOption::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordSelectOption> QDiscordSelectOption::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordSelectOption> out(new QDiscordSelectOption());
	out->deserialize(object);
	return out;
}


QDiscordSelectOption::QDiscordSelectOption(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordSelectOption::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordSelectOption::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordInteractionData> QDiscordInteractionData::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordInteractionData> out(new QDiscordInteractionData());
	out->deserialize(object);
	return out;
}


QDiscordInteractionData::QDiscordInteractionData(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordInteractionData::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordInteractionData::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordInteraction> QDiscordInteraction::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordInteraction> out(new QDiscordInteraction());
	out->deserialize(object);
	return out;
}


QDiscordInteraction::QDiscordInteraction(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordInteraction::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordInteraction::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordInteractionCallbackData> QDiscordInteractionCallbackData::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordInteractionCallbackData> out(new QDiscordInteractionCallbackData());
	out->deserialize(object);
	return out;
}


QDiscordInteractionCallbackData::QDiscordInteractionCallbackData(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordInteractionCallbackData::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordInteractionCallbackData::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordInteractionResponse> QDiscordInteractionResponse::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordInteractionResponse> out(new QDiscordInteractionResponse());
	out->deserialize(object);
	return out;
}


QDiscordInteractionResponse::QDiscordInteractionResponse(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordInteractionResponse::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordInteractionResponse::serialize() const
{
	return serializeJson();
}


void QDiscordInteractionResponse::send(QDiscordRest& rest, const QDiscordID& interaction_id, const QString& interaction_token)
{
	QJsonObject data = serialize();
	QDiscordRoute route = QDiscordRoutes::Interactions::createInteractionResponse(interaction_id, interaction_token);
	rest.request(route, data);
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordInteraction::InteractionType& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordInteraction::InteractionType::PING;
		break;
	case 2:
		value = QDiscordInteraction::InteractionType::APPLICATION_COMMAND;
		break;
	case 3:
		value = QDiscordInteraction::InteractionType::MESSAGE_COMPONENT;
		break;
	case 4:
		value = QDiscordInteraction::InteractionType::APPLICATION_COMMAND_AUTOCOMPLETE;
		break;
	case 5:
		value = QDiscordInteraction::InteractionType::MODAL_SUBMIT;
		break;
	default:
		value = QDiscordInteraction::InteractionType::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordInteraction::InteractionType& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, std::optional<MessageComponentType>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		switch (action.data()[name].toInt())
		{
		case 1:
			value = MessageComponentType::ActionRow;
			break;
		case 2:
			value = MessageComponentType::Button;
			break;
		case 3:
			value = MessageComponentType::SelectMenu;
			break;
		case 4:
			value = MessageComponentType::TextInput;
			break;
		default:
			value = MessageComponentType::Unknown;
		}
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const std::optional<MessageComponentType>& value, const QString& name)
{
	if (value.has_value())
	{
		action.data().insert(name, static_cast<int>(value.value()));
	}
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordInteractionResponse::InteractionCallbackType& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordInteractionResponse::InteractionCallbackType::PONG;
		break;
	case 4:
		value = QDiscordInteractionResponse::InteractionCallbackType::CHANNEL_MESSAGE_WITH_SOURCE;
		break;
	case 5:
		value = QDiscordInteractionResponse::InteractionCallbackType::DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE;
		break;
	case 6:
		value = QDiscordInteractionResponse::InteractionCallbackType::DEFERRED_UPDATE_MESSAGE;
		break;
	case 7:
		value = QDiscordInteractionResponse::InteractionCallbackType::UPDATE_MESSAGE;
		break;
	case 8:
		value = QDiscordInteractionResponse::InteractionCallbackType::APPLICATION_COMMAND_AUTOCOMPLETE_RESULT;
		break;
	case 9:
		value = QDiscordInteractionResponse::InteractionCallbackType::MODAL;
		break;
	default:
		value = QDiscordInteractionResponse::InteractionCallbackType::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordInteractionResponse::InteractionCallbackType& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QMap<QString, QString>& value, const QString& name)
{
	for (const QJsonValue& item : action.data()[name].toArray())
	{
		auto array = item.toArray(); // { "ru", "blabla" },
		if (array.size() == 2)
		{
			value.insert(array.at(0).toString(), array.at(1).toString());
		}
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QMap<QString, QString>& value, const QString& name)
{
	QJsonArray array;
	for (QMap<QString, QString>::const_iterator iter = value.begin(); iter != value.end(); ++iter)
	{
		QJsonArray obj;
		obj.append(QJsonValue(iter.key()));
		obj.append(QJsonValue(iter.value()));
		array.append(obj);
	}
	action.data().insert(name, array);
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, std::variant<QString, int, double>& value, const QString& name)
{
	value = std::forward<QString>(action.data()[name].toString());
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const std::variant<QString, int, double>& value, const QString& name)
{
	const QString* val1 = std::get_if<QString>(&value);
	if (val1)
	{
		action.data().insert(name, *val1);
		return;
	}
	const int* val2 = std::get_if<int>(&value);
	if (val2)
	{
		action.data().insert(name, *val2);
		return;
	}
	const double* val3 = std::get_if<double>(&value);
	if (val3)
	{
		action.data().insert(name, *val3);
		return;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, std::optional<std::variant<QString, int, double>>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		value = std::forward<QString>(action.data()[name].toString());
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const std::optional<std::variant<QString, int, double>>& value, const QString& name)
{
	if (value.has_value())
	{
		const QString* val1 = std::get_if<QString>(&value.value());
		if (val1)
		{
			action.data().insert(name, *val1);
			return;
		}
		const int* val2 = std::get_if<int>(&value.value());
		if (val2)
		{
			action.data().insert(name, *val2);
			return;
		}
		const double* val3 = std::get_if<double>(&value.value());
		if (val3)
		{
			action.data().insert(name, *val3);
			return;
		}
	}
}


