

void initslide (struct SLIDE* slide)
{
    slide->state = SLIDE_close;

    //start state
    ui->fermer.etat =  B_NORMAL;
    ui->creermob.etat =  B_NORMAL;
    ui->supprmob.etat =  B_NORMAL;

    setPos4(&ui->fermer.pos, screenw-44, screenh-84, 40,40);
    setPos4(&ui->creermob.pos, screenw-260, 122, 120,40);
    setPos4(&ui->supprmob.pos, screenw-130, 122, 120,40);

    ui->fermer.texture =        loadTexture ("rs/ui/fermer.png");
    ui->creermob.texture =        loadTexture ("rs/ui/creer.png");
    ui->supprmob.texture =        loadTexture ("rs/ui/suppr.png");

    if (glIsTexture(ui->fermer.texture) == GL_FALSE          ||
        glIsTexture(ui->supprmob.texture) == GL_FALSE          ||
        glIsTexture(ui->creermob.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }

    ui->ListeNb = 0;

    ui->ListeBouton[ui->ListeNb] = &ui->creer;        ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->quitter;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->charger;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->enregistrer;  ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->loadmap;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->depart;       ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->monster;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->fermer;       ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->creermob;      ui->ListeNb++;
    ui->ListeBouton[ui->ListeNb] = &ui->supprmob;
}
