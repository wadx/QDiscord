
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"
#include "QDiscordId.h"
#include "QDiscordUser.h"


class QDiscordSticker
	: public QDiscordModelBase<QDiscordSticker>
{
	Q_GADGET
public:
	enum class Type : qint8
	{
		STANDARD = 1, // an official sticker in a pack, part of Nitro or in a removed purchasable pack
		GUILD    = 2, // a sticker uploaded to a Boosted guild for the guild's members
		Unknown = -1
	};
	Q_ENUM(Type)

	enum class StickerFormat : qint8
	{
		PNG    = 1,
		APNG   = 2,
		LOTTIE = 3,
		Unknown = -1
	};
	Q_ENUM(StickerFormat)

	static QSharedPointer<QDiscordSticker> fromJson(const QJsonObject& object);
	QDiscordSticker(const QJsonObject& object);
	QDiscordSticker() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._pack_id, "pack_id");
		field(a, self._name, "name");
		field(a, self._description, "description");
		field(a, self._tags, "tags");
		field(a, self._asset, "asset");
		field(a, self._type, "type");
		field(a, self._format_type, "format_type");
		field(a, self._available, "available");
		field(a, self._guild_id, "guild_id");
		field(a, self._user, "user");
		field(a, self._sort_value, "sort_value");
	}

private:
	QDiscordID                  _id;             // id of the sticker
	QDiscordID                  _pack_id;        // for standard stickers, id of the pack the sticker is from
	QString                     _name;           // name of the sticker
	std::optional<QString>      _description;    // description of the sticker
	QString                     _tags;           // autocomplete/suggestion tags for the sticker (max 200 characters)
	std::optional<QString>      _asset;          // Deprecated previously the sticker asset hash, now an empty string
	Type                        _type = Type::Unknown; // type of sticker
	StickerFormat               _format_type = StickerFormat::Unknown; // type of sticker format
	std::optional<bool>         _available;      // whether this guild sticker can be used, may be false due to loss of Server Boosts
	std::optional<QDiscordID>   _guild_id;       // id of the guild that owns this sticker
	std::optional<QDiscordUser> _user;           // the user that uploaded the guild sticker
	std::optional<int>          _sort_value;     // the standard sticker's sort order within its pack
};
Q_DECLARE_METATYPE(QDiscordSticker)


class QDiscordStickerItem
	: public QDiscordModelBase<QDiscordStickerItem>
{
	Q_GADGET
public:

	static QSharedPointer<QDiscordStickerItem> fromJson(const QJsonObject& object);
	QDiscordStickerItem(const QJsonObject& object);
	QDiscordStickerItem() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._name, "name");
		field(a, self._format_type, "format_type");
	}

private:
	QDiscordID                     _id;             // id of the sticker
	QString                        _name;           // name of the sticker
	QDiscordSticker::StickerFormat _format_type = QDiscordSticker::StickerFormat::Unknown; // type of sticker format
};
Q_DECLARE_METATYPE(QDiscordStickerItem)


class QDiscordStickerPack
	: public QDiscordModelBase<QDiscordStickerPack>
{
	Q_GADGET
public:

	static QSharedPointer<QDiscordStickerPack> fromJson(const QJsonObject& object);
	QDiscordStickerPack(const QJsonObject& object);
	QDiscordStickerPack() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._id, "id");
		field(a, self._stickers, "stickers");
		field(a, self._name, "name");
		field(a, self._sku_id, "sku_id");
		field(a, self._cover_sticker_id, "cover_sticker_id");
		field(a, self._description, "description");
		field(a, self._banner_asset_id, "banner_asset_id");
	}

private:
	QDiscordID                     _id;               // id of the sticker pack
	QList<QDiscordSticker>         _stickers;         // the stickers in the pack
	QString                        _name;             // name of the sticker pack
	QDiscordID                     _sku_id;           // id of the pack's SKU
	std::optional<QDiscordID>      _cover_sticker_id; // id of a sticker in the pack which is shown as the pack's icon
	QString                        _description;      // description of the sticker pack
	std::optional<QDiscordID>      _banner_asset_id;  // id of the sticker pack's banner image
};
Q_DECLARE_METATYPE(QDiscordStickerPack)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordSticker::Type& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordSticker::Type& value, const QString& name);
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordSticker::StickerFormat& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordSticker::StickerFormat& value, const QString& name);
}; // namespace QDiscordModel

