// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2025
#pragma once

#define ICON(name, value) const auto name##_ICON = QStringLiteral(value)

namespace AyuAssets {

ICON(DEFAULT, "default");
ICON(DEFAULT_MACOS, "macos");
ICON(ALT, "alt");
ICON(DISCORD, "discord");
ICON(SPOTIFY, "spotify");
ICON(EXTERA, "extera");
ICON(NOTHING, "nothing");
ICON(BARD, "bard");
ICON(YAPLUS, "yaplus");
ICON(WIN95, "win95");
ICON(CHIBI, "chibi");
ICON(CHIBI2, "chibi2");
ICON(EXTERA2, "extera2");

void loadAppIco();

QImage loadPreview(QString name);

QString currentAppLogoName();
QImage currentAppLogo();
QImage currentAppLogoNoMargin();

}
