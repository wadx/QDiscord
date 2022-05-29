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

class QDateTime;


namespace QDiscordModel
{

template<class Action, typename T>
void field(Action& action, T& value, const QString& name);


class SerializeJsonAction
{
public:
	SerializeJsonAction(){};
	QJsonObject& data() { return _data; }
private:
	QJsonObject _data;
};


class DeserializeJsonAction
{
public:
	DeserializeJsonAction(const QJsonObject& data)
		: _data(data){};
	const QJsonObject& data() const { return _data; }
private:
	const QJsonObject& _data;
};

}; // namespace QDiscordModel


class SerializableJson
{};


template<class T>
class QDiscordModelBase : public SerializableJson
{
protected:
	Q_INVOKABLE void deserializeJson(const QJsonObject& object)
	{
		QDiscordModel::DeserializeJsonAction deserializeAction(object);
		static_cast<T*>(this)->map(deserializeAction);
	}

	Q_INVOKABLE QJsonObject serializeJson() const
	{
		QDiscordModel::SerializeJsonAction serializeAction;
		static_cast<const T*>(this)->map(serializeAction);
		return serializeAction.data();
	}
};


namespace QDiscordModel
{


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, T& value, const QString& name)
{
	T newVal;
	newVal.deserialize(action.data()[name].toObject());
	value = newVal;
}


template<>
void field(QDiscordModel::DeserializeJsonAction& action, QString& value, const QString& name);

template<>
void field(QDiscordModel::DeserializeJsonAction& action, QStringList& value, const QString& name);

template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<QString>& value, const QString& name);

template<>
void field(QDiscordModel::DeserializeJsonAction& action, double& value, const QString& name);

template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<double>& value, const QString& name);

template<>
void field(QDiscordModel::DeserializeJsonAction& action, bool& value, const QString& name);

template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<bool>& value, const QString& name);


template<typename T, typename std::enable_if<std::numeric_limits<T>::is_integer>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, T& value, const QString& name)
{
	value = action.data()[name].toVariant().value<T>();
}


template<typename T, typename std::enable_if<std::numeric_limits<T>::is_integer>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<T>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		value = action.data()[name].toVariant().value<T>();
	}
}


template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDateTime& value, const QString& name);

template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDateTime>& value, const QString& name);


template<typename T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, QList<T>& value, const QString& name)
{
	value.clear();
	for(const QJsonValue& i : action.data()[name].toArray())
	{
		T item;
		item.deserialize(i.toObject());
		value.append(item);
	}
}


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const T& value, const QString& name)
{
	action.data().insert(name, value.serialize());
}


template<>
void field(QDiscordModel::SerializeJsonAction& action, const QString& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const QStringList& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<QString>& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const double& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<double>& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const bool& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<bool>& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDateTime& value, const QString& name);

template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDateTime>& value, const QString& name);


template<typename T, typename std::enable_if<std::numeric_limits<T>::is_integer>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const T& value, const QString& name)
{
	action.data().insert(name, static_cast<const double>(value));
}


template<typename T, typename std::enable_if<std::numeric_limits<T>::is_integer>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<T>& value, const QString& name)
{
	if (value.has_value())
	{
		action.data().insert(name, value.value());
	}
}


template<typename T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const QList<T>& value, const QString& name)
{
	QJsonArray output;
	for (const T& i : value)
	{
		output.append(i.serialize());
	}
	action.data().insert(name, output);
}


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<T>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		value = T(action.data()[name].toObject());
	}
}


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<T>& value, const QString& name)
{
	if (value.has_value())
	{
		action.data().insert(name, value.value().serialize());
	}
}


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, QSharedPointer<T>& value, const QString& name)
{
	if (action.data().contains(name))
	{
		value = T::fromJson(action.data()[name].toObject());
	}
}


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const QSharedPointer<T>& value, const QString& name)
{
	if (value)
	{
		action.data().insert(name, value->serialize());
	}
}


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, QList<QSharedPointer<T>>& value, const QString& name)
{
	value.clear();
	for (const QJsonValue& i : action.data()[name].toArray())
	{
		QSharedPointer<T> item = T::fromJson(i.toObject());
		value.append(item);
	}
}


template<class T, typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const QList<QSharedPointer<T>>& value, const QString& name)
{
	QJsonArray output;
	for (const QSharedPointer<T>& i : value)
	{
		output.append(i->serialize());
	}
	action.data().insert(name, output);
}


} // namespace QDiscordModel

