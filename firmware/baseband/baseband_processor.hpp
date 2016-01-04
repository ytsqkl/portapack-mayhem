/*
 * Copyright (C) 2014 Jared Boone, ShareBrained Technology, Inc.
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __BASEBAND_PROCESSOR_H__
#define __BASEBAND_PROCESSOR_H__

#include "dsp_types.hpp"
#include "complex.hpp"

#include "channel_stats_collector.hpp"
#include "audio_stats_collector.hpp"

#include <array>
#include <cstdint>
#include <complex>

class BasebandProcessor {
public:
	virtual ~BasebandProcessor() = default;

	virtual void execute(const buffer_c8_t& buffer) = 0;

	virtual void on_message(const Message* const) { };
	virtual void on_update_spectrum() { };

protected:
	void feed_channel_stats(const buffer_c16_t& channel);

	void fill_audio_buffer(const buffer_s16_t& audio);
	void mute_audio();

private:
	ChannelStatsCollector channel_stats;
	AudioStatsCollector audio_stats;

	void feed_audio_stats(const buffer_s16_t& audio);
};

#endif/*__BASEBAND_PROCESSOR_H__*/
