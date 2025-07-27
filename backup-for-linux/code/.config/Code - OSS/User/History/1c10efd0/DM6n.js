require('dotenv').config()
const TOKEN = process.env.DISCORD

const {
    Client,
    GatewayIntentBits,
    EmbedBuilder,
    SlashCommandBuilder,
    ButtonBuilder,
    ModalBuilder,
    ButtonStyle,
    TextInputBuilder,
    TextInputStyle,
    ActionRowBuilder,
    Events,
    MessageFlags,
    ChannelType,
    PermissionFlagsBits,
    Guild
} = require('discord.js');

const client = new Client({
    intents: [
        GatewayIntentBits.Guilds,
        GatewayIntentBits.GuildMembers,
        GatewayIntentBits.GuildMessages,
        GatewayIntentBits.MessageContent,
        GatewayIntentBits.DirectMessages,
    ],
});

client.once('ready', async () => {
    const guild of client.guilds.cache.values();
    const member = await guild.members.fetchMe();
    await console.log(member);
});

client.login(TOKEN);
