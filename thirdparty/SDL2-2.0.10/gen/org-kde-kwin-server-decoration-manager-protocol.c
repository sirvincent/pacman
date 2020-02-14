/* Generated by wayland-scanner 1.17.0 */

/*
 * Copyright (C) 2015 Martin Gräßlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdint.h>
#include "wayland-util.h"

extern const struct wl_interface org_kde_kwin_server_decoration_interface;
extern const struct wl_interface wl_surface_interface;

static const struct wl_interface *types[] = {
	NULL,
	&org_kde_kwin_server_decoration_interface,
	&wl_surface_interface,
};

static const struct wl_message org_kde_kwin_server_decoration_manager_requests[] = {
	{ "create", "no", types + 1 },
};

static const struct wl_message org_kde_kwin_server_decoration_manager_events[] = {
	{ "default_mode", "u", types + 0 },
};

WL_EXPORT const struct wl_interface org_kde_kwin_server_decoration_manager_interface = {
	"org_kde_kwin_server_decoration_manager", 1,
	1, org_kde_kwin_server_decoration_manager_requests,
	1, org_kde_kwin_server_decoration_manager_events,
};

static const struct wl_message org_kde_kwin_server_decoration_requests[] = {
	{ "release", "", types + 0 },
	{ "request_mode", "u", types + 0 },
};

static const struct wl_message org_kde_kwin_server_decoration_events[] = {
	{ "mode", "u", types + 0 },
};

WL_EXPORT const struct wl_interface org_kde_kwin_server_decoration_interface = {
	"org_kde_kwin_server_decoration", 1,
	2, org_kde_kwin_server_decoration_requests,
	1, org_kde_kwin_server_decoration_events,
};

