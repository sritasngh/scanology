<?php
/***********************************************************
 * Copyright (C) 2014-2015, Siemens AG
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 ***********************************************************/

namespace Fossology\Scancode\Ui;

use Fossology\Lib\Plugin\AgentPlugin;

class ScancodeAgentPlugin extends AgentPlugin
{
  public function __construct() {
    $this->Name = "agent_scancode";
    $this->Title =  _("Scancode License Analysis");
    $this->AgentName = "scancode";

    parent::__construct();
  }

  function AgentHasResults($uploadId=0)
  {
    return CheckARS($uploadId, $this->AgentName, "scancode agent", "scancode_ars");
  }
  
  function preInstall()
  {
    if ($this->isScancodeInstalled()) {
      menu_insert("Agents::" . $this->Title, 0, $this->Name);
    }
  }
  
  public function isScancodeInstalled()
  {
    exec('which scancode', $lines, $returnVar);
    return (0==$returnVar);
  }
}

register_plugin(new ScancodeAgentPlugin());