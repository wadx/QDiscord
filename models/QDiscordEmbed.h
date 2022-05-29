
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"


class QDiscordEmbedFooter
	: public QDiscordModelBase<QDiscordEmbedFooter>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedFooter> fromJson(const QJsonObject& object);
	QDiscordEmbedFooter(const QJsonObject& object);
	QDiscordEmbedFooter() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._text, "text");
		field(a, self._icon_url, "icon_url");
		field(a, self._proxy_icon_url, "proxy_icon_url");
	}

private:
	QString                _text; // footer text
	std::optional<QString> _icon_url; // url of footer icon (only supports http(s) and attachments)
	std::optional<QString> _proxy_icon_url; // a proxied url of footer icon
};
Q_DECLARE_METATYPE(QDiscordEmbedFooter)


class QDiscordEmbedImage
	: public QDiscordModelBase<QDiscordEmbedImage>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedImage> fromJson(const QJsonObject& object);
	QDiscordEmbedImage(const QJsonObject& object);
	QDiscordEmbedImage() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._url, "url");
		field(a, self._proxy_url, "proxy_url");
		field(a, self._height, "height");
		field(a, self._width, "width");
	}

private:
	QString                _url; // source url of image (only supports http(s) and attachments)
	std::optional<QString> _proxy_url; // a proxied url of the image
	std::optional<int>     _height; // height of image
	std::optional<int>     _width; // width of image
};
Q_DECLARE_METATYPE(QDiscordEmbedImage)


class QDiscordEmbedThumbnail
	: public QDiscordModelBase<QDiscordEmbedThumbnail>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedThumbnail> fromJson(const QJsonObject& object);
	QDiscordEmbedThumbnail(const QJsonObject& object);
	QDiscordEmbedThumbnail() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._url, "url");
		field(a, self._proxy_url, "proxy_url");
		field(a, self._height, "height");
		field(a, self._width, "width");
	}

private:
	QString                _url; // source url of thumbnail (only supports http(s) and attachments)
	std::optional<QString> _proxy_url; // a proxied url of the thumbnail
	std::optional<int>     _height; // height of thumbnail
	std::optional<int>     _width; // width of thumbnail
};
Q_DECLARE_METATYPE(QDiscordEmbedThumbnail)


class QDiscordEmbedVideo
	: public QDiscordModelBase<QDiscordEmbedVideo>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedVideo> fromJson(const QJsonObject& object);
	QDiscordEmbedVideo(const QJsonObject& object);
	QDiscordEmbedVideo() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._url, "url");
		field(a, self._proxy_url, "proxy_url");
		field(a, self._height, "height");
		field(a, self._width, "width");
	}

private:
	QString                _url; // source url of video
	std::optional<QString> _proxy_url; // a proxied url of the video
	std::optional<int>     _height; // height of video
	std::optional<int>     _width; // width of video
};
Q_DECLARE_METATYPE(QDiscordEmbedVideo)


class QDiscordEmbedProvider
	: public QDiscordModelBase<QDiscordEmbedProvider>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedProvider> fromJson(const QJsonObject& object);
	QDiscordEmbedProvider(const QJsonObject& object);
	QDiscordEmbedProvider() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._url, "url");
	}

private:
	std::optional<QString> _name; // name of provider
	std::optional<QString> _url; // url of provider
};
Q_DECLARE_METATYPE(QDiscordEmbedProvider)


class QDiscordEmbedAuthor
	: public QDiscordModelBase<QDiscordEmbedAuthor>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedAuthor> fromJson(const QJsonObject& object);
	QDiscordEmbedAuthor(const QJsonObject& object);
	QDiscordEmbedAuthor() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._url, "url");
		field(a, self._icon_url, "icon_url");
		field(a, self._proxy_icon_url, "proxy_icon_url");
	}

private:
	QString                _name; // name of author
	std::optional<QString> _url; // url of author
	std::optional<QString> _icon_url; // url of author icon (only supports http(s) and attachments)
	std::optional<QString> _proxy_icon_url; // a proxied url of author icon
};
Q_DECLARE_METATYPE(QDiscordEmbedAuthor)


class QDiscordEmbedField
	: public QDiscordModelBase<QDiscordEmbedField>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedField> fromJson(const QJsonObject& object);
	QDiscordEmbedField(const QJsonObject& object);
	QDiscordEmbedField() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._value, "value");
		field(a, self._Inline, "inline");
	}

private:
	QString             _name; // name of field
	QString             _value; // name of field
	std::optional<bool> _Inline; // whether or not this field should display inline
};
Q_DECLARE_METATYPE(QDiscordEmbedField)


class QDiscordEmbed
	: public QDiscordModelBase<QDiscordEmbed>
{
	Q_GADGET
public:
	enum class Type : qint8
	{
		rich, // generic embed rendered from embed attributes
		image, // image embed
		video, // video embed
		gifv, // animated gif image embed rendered as a video embed
		article, // article embed
		link, // link embed
		Unknown
	};
	Q_ENUM(Type)

	static QSharedPointer<QDiscordEmbed> fromJson(const QJsonObject& object);
	QDiscordEmbed(const QJsonObject& object);
	QDiscordEmbed() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._title, "title");
		field(a, self._type, "type");
		field(a, self._description, "description");
		field(a, self._url, "url");
		field(a, self._timestamp, "timestamp");
		field(a, self._color, "color");
		field(a, self._footer, "footer");
		field(a, self._image, "image");
		field(a, self._thumbnail, "thumbnail");
		field(a, self._video, "video");
		field(a, self._provider, "provider");
		field(a, self._author, "author");
		field(a, self._fields, "fields");
	}

private:
	std::optional<QString>                _title;       // title of embed
	Type                                  _type = Type::Unknown; // type of embed (always "rich" for webhook embeds)
	std::optional<QString>                _description; // description of embed
	std::optional<QString>                _url;         // url of embed
	std::optional<QDateTime>              _timestamp;   // timestamp of embed content
	std::optional<int>                    _color;       // color code of the embed
	std::optional<QDiscordEmbedFooter>    _footer;      // footer information
	std::optional<QDiscordEmbedImage>     _image;       // image information
	std::optional<QDiscordEmbedThumbnail> _thumbnail;   // thumbnail information
	std::optional<QDiscordEmbedVideo>     _video;       // video information
	std::optional<QDiscordEmbedProvider>  _provider;    // provider information
	std::optional<QDiscordEmbedAuthor>    _author;      // author information
	QList<QDiscordEmbedField>             _fields;      // fields information
};
Q_DECLARE_METATYPE(QDiscordEmbed)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordEmbed::Type& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordEmbed::Type& value, const QString& name);
}; // namespace QDiscordModel

