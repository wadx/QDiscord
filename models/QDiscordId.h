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
#include "QDiscordUtilities.h"


class QDiscordID
{
	Q_GADGET

	Q_PROPERTY(quint64 value READ value WRITE setValue)
	Q_PROPERTY(QDateTime createdAt READ createdAt STORED false)

public:
	static QDiscordID generate();

	QDiscordID();
	explicit QDiscordID(quint64 id);
	QDiscordID(const char* id);
	QDiscordID(const QString& id);
	QDiscordID(const QDiscordID&) = default;
	Q_INVOKABLE QString toString() const;
	quint64 value() const;
	void setValue(const quint64 value);
	QDateTime createdAt() const;
	bool isNull() const;
	operator bool() const;
	bool operator!() const;
	bool operator==(const QDiscordID& other) const;
	bool operator!=(const QDiscordID& other) const;
	bool operator>(const QDiscordID& other) const;
	bool operator<(const QDiscordID& other) const;
	bool operator<=(const QDiscordID& other) const;
	bool operator>=(const QDiscordID& other) const;
	bool operator==(quint64 other) const;
	bool operator!=(quint64 other) const;
	bool operator>(quint64 other) const;
	bool operator<(quint64 other) const;
	bool operator<=(quint64 other) const;
	bool operator>=(quint64 other) const;

private:
	quint64 _id;
};

Q_DECLARE_METATYPE(QDiscordID)


namespace QDiscordModel
{

template<class T>
class CompareById
{
public:
	bool operator==(const T& other) const
	{
		return static_cast<const T*>(this)->id() == other.id();
	}
	bool operator!=(const T& other) const
	{
		return !operator==(other);
	}
	bool operator<(const T& other) const
	{
		return static_cast<const T*>(this)->id() < other.id();
	}
	bool operator>(const T& other) const
	{
		return static_cast<const T*>(this)->id() > other.id();
	}
	bool operator<=(const T& other) const
	{
		return static_cast<const T*>(this)->id() <= other.id();
	}
	bool operator>=(const T& other) const
	{
		return static_cast<const T*>(this)->id() >= other.id();
	}
	bool isNull() const
	{
		return !static_cast<const T*>(this)->id();
	}
	operator bool() const
	{
		return static_cast<const T*>(this)->id();
	}
};


template<typename T,
	typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr,
	typename std::enable_if<std::is_base_of<CompareById<T>, T>::value>::type* = nullptr>
void field(QDiscordModel::DeserializeJsonAction& action, QMap<QDiscordID, QSharedPointer<T>>& value, const QString& name)
{
	for(const QJsonValue& item : action.data()[name].toArray())
	{
		QSharedPointer<T> element = QSharedPointer<T>(new T());
		element->deserialize(item.toObject());
		value.insert(element->id(), element);
	}
}


template<typename T,
	typename std::enable_if<std::is_base_of<SerializableJson, T>::value>::type* = nullptr,
	typename std::enable_if<std::is_base_of<CompareById<T>, T>::value>::type* = nullptr>
void field(QDiscordModel::SerializeJsonAction& action, const QMap<QDiscordID, QSharedPointer<T>>& value, const QString& name)
{
	QJsonArray array;
	for (const QSharedPointer<T>& item : value)
	{
		array.append(item->serialize());
	}
	action.data().insert(name, array);
}


template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordID& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordID& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QList<QDiscordID>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QList<QDiscordID>& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, std::optional<QDiscordID>& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const std::optional<QDiscordID>& value, const QString& name);

} // namespace QDiscordModel


template<class T>
class QDiscordMapIdToObject : public QMap<QDiscordID, T>
{
};


namespace QDiscordModel
{
template<typename T>
	void field(QDiscordModel::DeserializeJsonAction& action, QDiscordMapIdToObject<QSharedPointer<T>>& value, const QString& name)
{
	QJsonObject object = action.data()[name].toObject();
	for (const QString& key : object.keys())
	{
		QSharedPointer<T> element = QSharedPointer<T>(new T());
		element->deserialize(object[key].toObject());
		value.insert(QDiscordID(key), element);
	}
}


template<typename T>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordMapIdToObject<QSharedPointer<T>>& value, const QString& name)
{
	QJsonObject object;
	for( auto iter = value.cbegin(); iter != value.cend(); ++iter)
	{
		object[iter.key().toString()] = iter.value()->serialize();
	}
	action.data().insert(name, object);
}

} // namespace QDiscordModel

