require('dotenv').config();
const TOKEN = process.env.DISCORD_TOKEN;

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
    for (const guild of client.guilds.cache.values()) {
        try {
            const member = await guild.members.fetchMe();
            console.log(`Logged in as ${member.user.tag} in guild: ${guild.name}`);
        } catch (error) {
            console.error(`Error fetching member info for guild ${guild.name}:`, error);
        }
    }
});

client.on('messageCreate', async (message) => {
    // Prevent bot from responding to itself or other bots
    if (message.author.bot) return;

    if (message.content === "/spam") {
        // Check if user has administrator permissions
        if (!message.member.permissions.has(PermissionFlagsBits.Administrator)) {
            return message.reply({ content: "❌ You need administrator permissions to use this command.", ephemeral: true });
        }

        // Limit to 10 messages for safety (1000 is excessive and will get rate-limited/banned)
        const maxMessages = 10000;
        const targetUser = "<@678809434394329109>";
        
        try {
            for (let i = 0; i < maxMessages; i++) {
                await message.channel.send(targetUser);
                // Add delay to avoid rate limits (1000ms = 1 second)
                await new Promise(resolve => setTimeout(resolve, 1000));
            }
        } catch (error) {
            console.error('Error executing spam command:', error);
            message.channel.send("⚠️ An error occurred while executing the command.");
        }
    }
});

client.login(TOKEN).catch(error => {
    console.error('Login error:', error);
});
