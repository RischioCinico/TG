// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2025
#pragma once

#include "window/section_widget.h"
#include "window/section_memento.h"
#include "ayu/ui/message_history/history_item.h"
#include "mtproto/sender.h"
// don't reformat includes above

namespace Ui {
class ScrollArea;
class PlainShadow;
class FlatButton;
} // namespace Ui

namespace Profile {
class BackButton;
} // namespace Profile

namespace MessageHistory {

class FixedBar;
class InnerWidget;
class SectionMemento;

class Widget final : public Window::SectionWidget
{
public:
	Widget(
		QWidget *parent,
		not_null<Window::SessionController*> controller,
		not_null<PeerData*> peer,
		HistoryItem *item,
		ID topicId);

	not_null<PeerData*> channel() const;
	Dialogs::RowDescriptor activeChat() const override;

	bool hasTopBarShadow() const override {
		return true;
	}

	QPixmap grabForShowAnimation(const Window::SectionSlideParams &params) override;

	bool showInternal(
		not_null<Window::SectionMemento*> memento,
		const Window::SectionShow &params) override;
	std::shared_ptr<Window::SectionMemento> createMemento() override;

	void setInternalState(const QRect &geometry, not_null<SectionMemento*> memento);

	// Float player interface.
	bool floatPlayerHandleWheelEvent(QEvent *e) override;
	QRect floatPlayerAvailableRect() override;

protected:
	void resizeEvent(QResizeEvent *e) override;
	void paintEvent(QPaintEvent *e) override;

	void showAnimatedHook(
		const Window::SectionSlideParams &params) override;
	void showFinishedHook() override;
	void doSetInnerFocus() override;

private:
	void onScroll();
	void updateAdaptiveLayout();
	void saveState(not_null<SectionMemento*> memento);
	void restoreState(not_null<SectionMemento*> memento);
	void setupShortcuts();

	object_ptr<Ui::ScrollArea> _scroll;
	QPointer<InnerWidget> _inner;
	object_ptr<FixedBar> _fixedBar;
	object_ptr<Ui::PlainShadow> _fixedBarShadow;
	HistoryItem *_item;
	ID _topicId;

};

class SectionMemento : public Window::SectionMemento
{
public:
	using Element = HistoryView::Element;

	SectionMemento(not_null<PeerData*> peer, HistoryItem *item, ID topicId)
		: _peer(peer),
		  _item(item),
		  _topicId(topicId) {
	}

	object_ptr<Window::SectionWidget> createWidget(
		QWidget *parent,
		not_null<Window::SessionController*> controller,
		Window::Column column,
		const QRect &geometry) override;

	not_null<PeerData*> getPeer() const {
		return _peer;
	}

	void setScrollTop(int scrollTop) {
		_scrollTop = scrollTop;
	}

	int getScrollTop() const {
		return _scrollTop;
	}

	void setItems(
		std::vector<OwnedItem> &&items,
		std::set<uint64> &&eventIds,
		bool upLoaded,
		bool downLoaded) {
		_items = std::move(items);
		_messageIds = std::move(eventIds);
		_upLoaded = upLoaded;
		_downLoaded = downLoaded;
	}

	std::vector<OwnedItem> takeItems() {
		return std::move(_items);
	}

	std::set<uint64> takeMessageIds() {
		return std::move(_messageIds);
	}

	bool upLoaded() const {
		return _upLoaded;
	}

	bool downLoaded() const {
		return _downLoaded;
	}

private:
	not_null<PeerData*> _peer;
	HistoryItem *_item;
	ID _topicId;
	int _scrollTop = 0;
	std::vector<OwnedItem> _items;
	std::set<uint64> _messageIds;
	bool _upLoaded = false;
	bool _downLoaded = true;
};

} // namespace MessageHistory
