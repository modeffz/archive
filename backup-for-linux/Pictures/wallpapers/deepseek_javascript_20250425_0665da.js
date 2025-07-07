// ... (импорты и начальная настройка остаются без изменений)

// В обработчике кнопок принятия/отклонения заявок:
else if(interaction.customId.startsWith('rp_category_')) {
    const [_, __, action, userId] = interaction.customId.split('_');
    const settings = serverSettings.get(`${interaction.guildId}_rp`);
    const member = await interaction.guild.members.fetch(userId);
    const admin = interaction.user;

    // Исправление ошибки с embed
    const originalEmbed = interaction.message.embeds[0];
    if (!originalEmbed) {
        return interaction.reply({
            content: '❌ Не удалось найти данные заявки',
            flags: MessageFlags.Ephemeral
        });
    }

    const embedData = originalEmbed.data;
    const categoryName = embedData.fields.find(f => f.name === "Название")?.value;
    const categoryDesc = embedData.fields.find(f => f.name === "Описание")?.value;
    const categoryRules = embedData.fields.find(f => f.name === "Правила")?.value;

    if(action === 'accept') {
        // Создаем роль для категории
        const role = await interaction.guild.roles.create({
            name: `RP-${categoryName}`,
            color: 'Random',
            reason: `Роль для RP категории ${categoryName}`
        });

        // Создаем категорию каналов (без родительской категории)
        const newCategory = await interaction.guild.channels.create({
            name: categoryName,
            type: ChannelType.GuildCategory,
            permissionOverwrites: [
                {
                    id: interaction.guild.id,
                    deny: ['ViewChannel']
                },
                {
                    id: role.id,
                    allow: ['ViewChannel']
                }
            ]
        });

        // Создаем каналы внутри категории
        const mainChannel = await interaction.guild.channels.create({
            name: 'общее',
            type: ChannelType.GuildText,
            parent: newCategory,
            permissionOverwrites: [
                {
                    id: interaction.guild.id,
                    deny: ['ViewChannel']
                },
                {
                    id: role.id,
                    allow: ['ViewChannel', 'SendMessages', 'ReadMessageHistory']
                }
            ]
        });

        const rulesChannel = await interaction.guild.channels.create({
            name: 'правила',
            type: ChannelType.GuildText,
            parent: newCategory,
            permissionOverwrites: [
                {
                    id: interaction.guild.id,
                    deny: ['ViewChannel']
                },
                {
                    id: role.id,
                    allow: ['ViewChannel', 'ReadMessageHistory']
                }
            ]
        });
        await rulesChannel.send(`**Правила категории ${categoryName}:**\n${categoryRules}`);

        // Даем создателю роль доступа
        await member.roles.add(role);

        // Сохраняем категорию
        settings.categories.push({
            id: newCategory.id,
            roleId: role.id,
            name: categoryName,
            description: categoryDesc,
            rules: categoryRules,
            createdBy: member.id,
            mainChannel: mainChannel.id
        });
        await SSettings();

        // Создаем новый embed с обновленной информацией
        const newEmbed = new EmbedBuilder()
            .setColor(0x00FF00) // Зеленый
            .setTitle(`Категория "${categoryName}" (Принято)`)
            .addFields(
                { name: "Описание", value: categoryDesc },
                { name: "Правила", value: categoryRules },
                { name: "Создатель", value: member.user.tag },
                { name: "Принял", value: admin.tag },
                { name: "Категория", value: newCategory.toString() },
                { name: "Роль доступа", value: role.toString() }
            );

        await interaction.message.edit({ 
            embeds: [newEmbed], 
            components: [] 
        });

        await interaction.reply({
            content: `✅ Категория "${categoryName}" создана!`,
            flags: MessageFlags.Ephemeral
        });

        await member.send({
            content: `✅ Ваша заявка на создание категории "${categoryName}" принята!\nВы получили доступ к: ${newCategory}`
        });
    } 
    else if(action === 'reject') {
        const newEmbed = new EmbedBuilder()
            .setColor(0xFF0000) // Красный
            .setTitle(`Заявка на категорию "${categoryName}" (Отклонено)`)
            .addFields(
                { name: "Описание", value: categoryDesc },
                { name: "Отклонил", value: admin.tag },
                { name: "Причина", value: "Не указана" }
            );

        await interaction.message.edit({ 
            embeds: [newEmbed], 
            components: [] 
        });

        await member.send({
            content: `❌ Ваша заявка на создание категории "${categoryName}" была отклонена`
        }).catch(() => {});

        await interaction.reply({
            content: `❌ Заявка на создание категории отклонена`,
            flags: MessageFlags.Ephemeral
        });
    }
}
else if(interaction.customId.startsWith('rp_access_')) {
    const [_, __, action, userId, categoryId] = interaction.customId.split('_');
    const settings = serverSettings.get(`${interaction.guildId}_rp`);
    const member = await interaction.guild.members.fetch(userId);
    const admin = interaction.user;

    // Исправление ошибки с embed
    const originalEmbed = interaction.message.embeds[0];
    if (!originalEmbed) {
        return interaction.reply({
            content: '❌ Не удалось найти данные заявки',
            flags: MessageFlags.Ephemeral
        });
    }

    const embedData = originalEmbed.data;
    const characterName = embedData.fields.find(f => f.name === "Имя персонажа")?.value;
    const category = settings.categories.find(c => c.id === categoryId);

    if(!category) {
        return interaction.reply({
            content: '❌ Категория не найдена',
            flags: MessageFlags.Ephemeral
        });
    }

    if(action === 'accept') {
        const role = interaction.guild.roles.cache.get(category.roleId);
        if(!role) {
            return interaction.reply({
                content: '❌ Роль доступа не найдена',
                flags: MessageFlags.Ephemeral
            });
        }

        // Даем пользователю роль доступа
        await member.roles.add(role);

        // Создаем новый embed с обновленной информацией
        const newEmbed = new EmbedBuilder()
            .setColor(0x00FF00) // Зеленый
            .setTitle(`Заявка на доступ (Принято)`)
            .addFields(
                { name: "Персонаж", value: characterName },
                { name: "Категория", value: category.name },
                { name: "Пользователь", value: member.user.tag },
                { name: "Принял", value: admin.tag },
                { name: "Роль доступа", value: role.toString() }
            );

        await interaction.message.edit({ 
            embeds: [newEmbed], 
            components: [] 
        });

        // Сохраняем персонажа
        settings.characters.push({
            name: characterName,
            ownerId: member.id,
            categoryId: categoryId,
            approvedBy: admin.id,
            approvedAt: new Date().toISOString()
        });
        await SSettings();

        await interaction.reply({
            content: `✅ Доступ к категории "${category.name}" выдан`,
            flags: MessageFlags.Ephemeral
        });

        await member.send({
            content: `✅ Ваша заявка на персонажа "${characterName}" принята!\nВы получили доступ к категории: ${category.name}`
        });
    } 
    else if(action === 'reject') {
        const newEmbed = new EmbedBuilder()
            .setColor(0xFF0000) // Красный
            .setTitle(`Заявка на доступ (Отклонено)`)
            .addFields(
                { name: "Персонаж", value: characterName },
                { name: "Категория", value: category.name },
                { name: "Отклонил", value: admin.tag },
                { name: "Причина", value: "Не указана" }
            );

        await interaction.message.edit({ 
            embeds: [newEmbed], 
            components: [] 
        });

        await member.send({
            content: `❌ Ваша заявка на персонажа "${characterName}" была отклонена`
        }).catch(() => {});

        await interaction.reply({
            content: `❌ Заявка на доступ отклонена`,
            flags: MessageFlags.Ephemeral
        });
    }
}

// ... (остальной код остается без изменений)