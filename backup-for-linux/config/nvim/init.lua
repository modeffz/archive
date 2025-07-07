-- Basic config
require("core.mappings")
require("core.plugins")
require("core.colors")
require("core.configs")

-- Plugins config
require("plugins.telescope")
require("plugins.lsp")
require("plugins.mason")
require("plugins.cmp")
-- require("plugins.nullls")
require("plugins.lualine")
require("plugins.gitsigns")
require("plugins.treesitter")
require("plugins.toggleterm")
require("plugins.outline")
require("plugins.autopairs")
require("plugins.comments")
-- require("plugins.autotag")
require("plugins.buffline")
require("plugins.neotree")
require("plugins.dashboard")
-- require("plugins.whichkey")

vim.api.nvim_create_autocmd("VimEnter", {
  callback = function()
    vim.g.which_key_disable_healthcheck = 1
  end
})

