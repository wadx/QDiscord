
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordMessageComponent.h"


QSharedPointer<QDiscordMessageComponent> QDiscordMessageComponent::fromJson(const QJsonObject& object)
{
	MessageComponentType type = static_cast<MessageComponentType>(object["type"].toInt());
	switch (type)
	{
	case MessageComponentType::ActionRow:
	{
		QSharedPointer<QDiscordMessageComponent> out(new QDiscordMessageComponent_ActionRow());
		out->deserialize(object);
		return out;
	}
	case MessageComponentType::Button:
	{
		QSharedPointer<QDiscordMessageComponent> out(new QDiscordMessageComponent_Button());
		out->deserialize(object);
		return out;
	}
	case MessageComponentType::SelectMenu:
	{
		QSharedPointer<QDiscordMessageComponent> out(new QDiscordMessageComponent_SelectMenu());
		out->deserialize(object);
		return out;
	}
	case MessageComponentType::TextInput:
	{
		QSharedPointer<QDiscordMessageComponent> out(new QDiscordMessageComponent_TextInput());
		out->deserialize(object);
		return out;
	}
	}
	return QSharedPointer<QDiscordMessageComponent>();
}


void QDiscordMessageComponent_ActionRow::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordMessageComponent_ActionRow::serialize() const
{
	return serializeJson();
}


void QDiscordMessageComponent_Button::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordMessageComponent_Button::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordSelectMenuOption> QDiscordSelectMenuOption::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordSelectMenuOption> out(new QDiscordSelectMenuOption());
	out->deserialize(object);
	return out;
}


QDiscordSelectMenuOption::QDiscordSelectMenuOption(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordSelectMenuOption::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordSelectMenuOption::serialize() const
{
	return serializeJson();
}


void QDiscordMessageComponent_SelectMenu::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordMessageComponent_SelectMenu::serialize() const
{
	return serializeJson();
}


void QDiscordMessageComponent_TextInput::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordMessageComponent_TextInput::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, MessageComponentType& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
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


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const MessageComponentType& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessageComponent_Button::ButtonStyle& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordMessageComponent_Button::ButtonStyle::Primary;
		break;
	case 2:
		value = QDiscordMessageComponent_Button::ButtonStyle::Secondary;
		break;
	case 3:
		value = QDiscordMessageComponent_Button::ButtonStyle::Success;
		break;
	case 4:
		value = QDiscordMessageComponent_Button::ButtonStyle::Danger;
		break;
	case 5:
		value = QDiscordMessageComponent_Button::ButtonStyle::Link;
		break;
	default:
		value = QDiscordMessageComponent_Button::ButtonStyle::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessageComponent_Button::ButtonStyle& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordMessageComponent_TextInput::TextInputStyle& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordMessageComponent_TextInput::TextInputStyle::Short;
		break;
	case 2:
		value = QDiscordMessageComponent_TextInput::TextInputStyle::Paragraph;
		break;
	default:
		value = QDiscordMessageComponent_TextInput::TextInputStyle::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordMessageComponent_TextInput::TextInputStyle& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


