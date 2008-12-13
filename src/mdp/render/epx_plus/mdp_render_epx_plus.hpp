/***************************************************************************
 * Gens: [MDP] EPX Plus renderer.                                          *
 *                                                                         *
 * Original code from Gens Rerecording.                                    *
 * MDP version Copyright (c) 2008 by David Korth                           *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; either version 2 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           *
 ***************************************************************************/

#ifndef MDP_RENDER_EPX_PLUS_HPP
#define MDP_RENDER_EPX_PLUS_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "mdp/mdp.h"
#include "mdp/mdp_render.h"
#include "mdp/mdp_host.h"

DLL_LOCAL void MDP_FNCALL mdp_render_epx_plus_init(MDP_Host_t *hostSrv);
DLL_LOCAL void MDP_FNCALL mdp_render_epx_plus_end(void);
DLL_LOCAL void MDP_FNCALL mdp_render_epx_plus_cpp(MDP_Render_Info_t *renderInfo);

#ifdef __cplusplus
}
#endif

#endif /* MDP_RENDER_EPX_PLUS_HPP */