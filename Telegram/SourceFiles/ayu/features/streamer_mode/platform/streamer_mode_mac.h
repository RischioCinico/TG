// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2025
#pragma once

namespace AyuFeatures::StreamerMode::Impl {

void enableHook();
void disableHook();
void hideWidgetWindow(QWidget *widget);
void showWidgetWindow(QWidget *widget);

}