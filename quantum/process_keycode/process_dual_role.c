/* Copyright 2017 Peter Jones <pjones@devalot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quantum.h"

static qk_dual_role_state_t dual_role_state = {0, 0, false, false};

// Start tracking a dual role key.
static inline void dual_role_start(uint16_t keycode, keyrecord_t *record) {
  dual_role_state.index = keycode - QK_DUAL_ROLE;
  dual_role_state.timer = timer_read();
  dual_role_state.active = true;
  dual_role_state.interrupted = false;
}

// The dual role should end now.
static inline void dual_role_end(uint16_t keycode, keyrecord_t *record) {
  if ((keycode - QK_DUAL_ROLE) != dual_role_state.index) {
    keycode = dual_role_keys[keycode - QK_DUAL_ROLE].key;
    unregister_code(keycode);
  }

  if (dual_role_state.interrupted ||
      timer_elapsed(dual_role_state.timer) > TAPPING_TERM)
  {
    // Key is done, and acted like a modifier.
    unregister_mods(dual_role_keys[dual_role_state.index].mod);
  } else {
    // Key is done, did not act like a modifier.
    register_code(dual_role_keys[dual_role_state.index].key);
    send_keyboard_report();
    unregister_code(dual_role_keys[dual_role_state.index].key);
  }

  dual_role_state.active = false;
}

// An existing dual role was interrupted.
static inline void dual_role_interrupted(uint16_t keycode, keyrecord_t *record) {
  dual_role_state.interrupted = true;
  register_mods(dual_role_keys[dual_role_state.index].mod);
  register_code(keycode);
}

bool process_dual_role(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case QK_DUAL_ROLE ... QK_DUAL_ROLE_MAX:
    if (record->event.pressed) {
      if (dual_role_state.active) {
        keycode = dual_role_keys[keycode - QK_DUAL_ROLE].key;
        dual_role_interrupted(keycode, record);
      } else {
        dual_role_start(keycode, record);
      }
    } else {
      dual_role_end(keycode, record);
    }

    return false;

  default:
    if (record->event.pressed && dual_role_state.active) {
      dual_role_interrupted(keycode, record);
      return false;
    }
  }

  return true;
}
