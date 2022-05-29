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

class QDiscordDiscriminator
{
	Q_GADGET

	Q_PROPERTY(qint16 value READ value WRITE setValue)

public:
	QDiscordDiscriminator();
	QDiscordDiscriminator(qint16 discriminator);
	QDiscordDiscriminator(const QString& discriminator);
	Q_INVOKABLE QString toString() const;
	qint16 value() const;
	void setValue(const qint16 value);
	bool isNull() const;
	operator bool() const;
	bool operator!() const;
	bool operator==(const QDiscordDiscriminator& other) const;
	bool operator!=(const QDiscordDiscriminator& other) const;
	bool operator>(const QDiscordDiscriminator& other) const;
	bool operator<(const QDiscordDiscriminator& other) const;
	bool operator<=(const QDiscordDiscriminator& other) const;
	bool operator>=(const QDiscordDiscriminator& other) const;
	bool operator==(qint16 other) const;
	bool operator!=(qint16 other) const;
	bool operator>(qint16 other) const;
	bool operator<(qint16 other) const;
	bool operator<=(qint16 other) const;
	bool operator>=(qint16 other) const;

private:
	qint16 _discriminator;
};

Q_DECLARE_METATYPE(QDiscordDiscriminator)

namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordDiscriminator& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordDiscriminator& value, const QString& name);
} // namespace QDiscordModel

