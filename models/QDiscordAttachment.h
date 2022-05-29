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

#include "QDiscordId.h"


class QDiscordAttachment
	: public QDiscordModelBase<QDiscordAttachment>
	, public QDiscordModel::CompareById<QDiscordAttachment>
{
	Q_GADGET

	Q_PROPERTY(QDiscordID dId READ id WRITE setId)
	Q_PROPERTY(QString filename READ filename WRITE setFilename)
	Q_PROPERTY(qint64 size READ size WRITE setSize)
	Q_PROPERTY(QString url READ url WRITE setUrl)
	Q_PROPERTY(QString proxyUrl READ proxyUrl WRITE setProxyUrl)
	Q_PROPERTY(std::optional<int> height READ height WRITE setHeight)
	Q_PROPERTY(std::optional<int> width READ width WRITE setWidth)

public:
	static QSharedPointer<QDiscordAttachment> fromJson(const QJsonObject& object);

	QDiscordAttachment(const QJsonObject& object);
	QDiscordAttachment() = default;

	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	QDiscordID id() const { return _id; }
	void setId(QDiscordID id) { _id = id; }
	const QString& filename() const { return _filename; }
	void setFilename(const QString& filename) { _filename = filename; }
	const std::optional<QString>& description() const { return _description; }
	void setDescription(const QString& description) { _description = description; }
	const std::optional<QString>& content_type() const { return _content_type; }
	void setContent_type(const QString& content_type) { _content_type = content_type; }
	qint64 size() const { return _size; }
	void setSize(qint64 size) { _size = size; }
	const QString& url() const { return _url; }
	void setUrl(const QString& url) { _url = url; }
	const QString& proxyUrl() const { return _proxyUrl; }
	void setProxyUrl(const QString& proxyUrl) { _proxyUrl = proxyUrl; }
	std::optional<int> height() const { return _height; }
	void setHeight(const std::optional<int>& height) { _height = height; }
	std::optional<int> width() const { return _width; }
	void setWidth(const std::optional<int>& width) { _width = width; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._filename, "filename");
		field(a, self._description, "description");
		field(a, self._content_type, "content_type");
		field(a, self._size, "size");
		field(a, self._url, "url");
		field(a, self._proxyUrl, "proxy_url");
		field(a, self._height, "height");
		field(a, self._width, "width");
		field(a, self._ephemeral, "ephemeral");
	}

private:
	QDiscordID             _id;           // attachment id
	QString                _filename;     // name of file attached
	std::optional<QString> _description;  // description for the file
	std::optional<QString> _content_type; // the attachment's media type
	qint64                 _size = -1;    // size of file in bytes
	QString                _url;          // source url of file
	QString                _proxyUrl;     // a proxied url of file
	std::optional<int>     _height;       // height of file (if image)
	std::optional<int>     _width;        // width of file (if image)
	std::optional<bool>    _ephemeral;    // whether this attachment is ephemeral
};
Q_DECLARE_METATYPE(QDiscordAttachment)

