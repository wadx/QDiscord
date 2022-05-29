
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordChannelMention.h"


QSharedPointer<QDiscordChannelMention> QDiscordChannelMention::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordChannelMention> out(new QDiscordChannelMention());
	out->deserialize(object);
	return out;
}


QDiscordChannelMention::QDiscordChannelMention(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordChannelMention::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordChannelMention::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordAllowedMentions> QDiscordAllowedMentions::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordAllowedMentions> out(new QDiscordAllowedMentions());
	out->deserialize(object);
	return out;
}


QDiscordAllowedMentions::QDiscordAllowedMentions(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordAllowedMentions::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordAllowedMentions::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordAllowedMentions::AllowedMentionType>& value, const QString& name)
{
	value.clear();
	for (const QJsonValue& i : action.data()[name].toArray())
	{
		QString v = i.toString();
		if (v == "roles")
		{
			value.append(QDiscordAllowedMentions::AllowedMentionType::RoleMentions);
		}
		else if (v == "users")
		{
			value.append(QDiscordAllowedMentions::AllowedMentionType::UserMentions);
		}
		else if (v == "everyone")
		{
			value.append(QDiscordAllowedMentions::AllowedMentionType::EveryoneMentions);
		}
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordAllowedMentions::AllowedMentionType>& value, const QString& name)
{
	QJsonArray output;
	for (const QDiscordAllowedMentions::AllowedMentionType& i : value)
	{
		switch (i)
		{
		case QDiscordAllowedMentions::AllowedMentionType::RoleMentions:
			output.append("roles");
			break;
		case QDiscordAllowedMentions::AllowedMentionType::UserMentions:
			output.append("users");
			break;
		case QDiscordAllowedMentions::AllowedMentionType::EveryoneMentions:
			output.append("everyone");
			break;
		}
	}
	if (output.size() > 0)
	{
		action.data().insert(name, output);
	}
}


