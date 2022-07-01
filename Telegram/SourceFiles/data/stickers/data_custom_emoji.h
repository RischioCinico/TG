/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "data/stickers/data_stickers_set.h"
#include "ui/text/custom_emoji_instance.h"
#include "base/timer.h"
#include "base/weak_ptr.h"

struct StickerSetIdentifier;

namespace Main {
class Session;
} // namespace Main

namespace Data {

class Session;
class CustomEmojiLoader;

struct CustomEmojiId {
	uint64 selfId = 0;
	uint64 id = 0;
	StickerSetIdentifier set;
};

class CustomEmojiManager final : public base::has_weak_ptr {
public:
	enum class SizeTag {
		Normal,
		Large,
	};

	CustomEmojiManager(not_null<Session*> owner);
	~CustomEmojiManager();

	[[nodiscard]] std::unique_ptr<Ui::Text::CustomEmoji> create(
		QStringView data,
		Fn<void()> update);

	[[nodiscard]] Main::Session &session() const;
	[[nodiscard]] Session &owner() const;

private:
	struct Set {
		int32 hash = 0;
		mtpRequestId requestId = 0;
		base::flat_set<uint64> documents;
		base::flat_set<uint64> waiting;
	};
	struct RepaintBunch {
		crl::time when = 0;
		std::vector<base::weak_ptr<Ui::CustomEmoji::Instance>> instances;
	};

	void requestSetIfNeeded(const CustomEmojiId &id);
	void repaintLater(
		not_null<Ui::CustomEmoji::Instance*> instance,
		Ui::CustomEmoji::RepaintRequest request);
	void scheduleRepaintTimer();
	void invokeRepaints();

	const not_null<Session*> _owner;

	base::flat_map<uint64, base::flat_map<
		uint64,
		std::unique_ptr<Ui::CustomEmoji::Instance>>> _instances;
	base::flat_map<uint64, Set> _sets;
	base::flat_map<
		uint64,
		std::vector<base::weak_ptr<CustomEmojiLoader>>> _loaders;

	base::flat_map<crl::time, RepaintBunch> _repaints;
	crl::time _repaintNext = 0;
	base::Timer _repaintTimer;
	bool _repaintTimerScheduled = false;

};

[[nodiscard]] QString SerializeCustomEmojiId(const CustomEmojiId &id);
[[nodiscard]] QString SerializeCustomEmojiId(
	not_null<DocumentData*> document);
[[nodiscard]] CustomEmojiId ParseCustomEmojiData(QStringView data);

} // namespace Data