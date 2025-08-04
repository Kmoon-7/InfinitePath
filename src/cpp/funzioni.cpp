#include "funzioni.hpp"

//fino a che il giocatore non vuole terminare il gioco lo fa ripartire
void funzioni::play(){
    
    srand(time (0));
    menuStart();
    wins = new windows(maxY, maxX);
    wins->inizializeWindows();
    wins->printMap();

    while(check_end){
        start_game();
    }
}

void funzioni::start_game(){
    int n;
    bool guardia;

    new_room();
    inizialize_map();
    avatar->is_first_room();
   
    while(check_game){
         
        shoot();
        walk();
        avatar->getk();
        

        check_life();

        if(list_levels->key_b && avatar->getOpen()){
            list_levels->key_b = false;
            f_key();
        }
        
        if(list_levels->artifact && avatar->getArtifact()){
            list_levels->artifact = false;
            getAbility();
            f_artifact();
        }

        if(avatar->getPrev())
            move_door(true);

        if(avatar->getNext())    
            move_door(false);

        if(avatar->getDead())
            End();

        if(avatar != NULL){
            if(avatar->getQuit())
            time_out();
        }
    }
    check_game = true;
}

//estrae e inserisce nella lista tutti i valori negessari per creare una stanza
void funzioni::new_room(){

    p_level tmp = new level;

    tmp->key_b = true;
    tmp->artifact = true;
    
    tmp->room = extract_random(3);

    for(int i=0; i<3; i++){
        tmp->Enemy[i] = extract_random(4);
    }

    if(list_levels != NULL)
        list_levels->next = tmp;

    tmp->next = NULL;
    tmp->prev = list_levels;
    list_levels = tmp;
}

//inizializza e stampa una nuova mappa
void funzioni::inizialize_map(){

    if(list_levels->room == 0){
        map_one = new mapOne(W,map_height,map_length);
        if(list_levels->key_b)
            map_one->door();
    } else if (list_levels->room == 1){
        map_two = new mapTwo(W,map_height,map_length);
        if(list_levels->key_b)
            map_two->door();
    } else {
        map_three = new mapThree(W,map_height,map_length);
        if(list_levels->key_b)
            map_three->door();
    }

    inizialize_key_art();
    inizialize_enemy();
    inizialize_mainC();

    if (ability == 1 || ability == 3)
        avatar->getFast();
    if (ability == 2 || ability == 3)
        avatar->getArrowFast();
}

//crea l'artefatto e la chiave se le bool kay e artifact sono true
void funzioni::inizialize_key_art(){

    if(list_levels->key_b){
        if(list_levels->room == 0){
            map_one->build_Key();
            Key = map_one->getKey();
        }
        else if (list_levels->room == 1){
            map_two->build_Key();
            Key = map_two->getKey();
        } else {
            map_three->build_Key();
            Key = map_three->getKey();
        }
    }

    if(list_levels->artifact){
        if(list_levels->room == 0){
            map_one->build_Art(ability);
            artifact = map_one->getArt();
        }
        else if (list_levels->room == 1){
            map_two->build_Art(ability);
            artifact = map_two->getArt();
        } else {
            map_three->build_Art(ability);
            artifact = map_three->getArt();
        }
    }
}

//estrae dalla mappa i valori di ogni cattivo e chiama la funzione push
//passandogli anche che tipologia di cattivo è
void funzioni::inizialize_enemy(){
    p_l_enemy tmp;
    
    for(int i=0; i<3; i++){

        if(list_levels->Enemy[i] < 4){

            tmp = new l_enemy;
            tmp->position = i;
            tmp->kind = list_levels->Enemy[i];

            if(list_levels->room == 0){
                map_one->create_enemy(i, list_levels->Enemy[i]);
                tmp->data = map_one->getEnemy(i);
            }
            else if (list_levels->room == 1){
                map_two->create_enemy(i, list_levels->Enemy[i]);
                tmp->data = map_two->getEnemy(i);
            } else {
                map_three->create_enemy(i, list_levels->Enemy[i]);
                tmp->data = map_three->getEnemy(i);
            }

            tmp->next = list_enemy;
            list_enemy = tmp;
        }
    }
}

//inizializza il protagonista
void funzioni::inizialize_mainC(){

    if(list_levels->room == 0){
        map_one->create_main(forward, life_main, posY, posX);
        avatar = map_one->getMain();
    }
    else if(list_levels->room == 1){
        map_two->create_main(forward, life_main, posY, posX);
        avatar = map_two->getMain();
    } else {
        map_three->create_main(forward, life_main, posY, posX);
        avatar = map_three->getMain();
    }
    
    if(!list_levels->key_b)
        avatar->OpenDoor();

    if(list_levels->prev == NULL)
        avatar->is_first_room();

}

//fa avanzare i personaggi e le frecce
void funzioni::walk(){

    p_l_enemy tmp = list_enemy;

    while(tmp != NULL){
        int i = tmp->kind;

        if(i == 0)
            ((cattivo *)(tmp->data))->walk();
        else if(i == 1){
            
            if(((cattivo_r *)(tmp->data))->getDirezionection()%2 == 0)
                ((cattivo_r *)(tmp->data))->run_after(avatar->getY());
            else ((cattivo_r *)(tmp->data))->run_after(avatar->getX());
        }
        else if(i == 2 || i == 3){
            ((cattivo_f *)(tmp->data))->arrow_walk();

            if(((cattivo_f *)(tmp->data))->getDirezionection()%2 == 0)
                ((cattivo_f *)(tmp->data))->run_after(avatar->getY());
            else ((cattivo_f *)(tmp->data))->run_after(avatar->getX());
        }

        tmp = tmp->next;
    }

    avatar->arrow_walk();
}

//spara le frecce dei nemici
void funzioni::shoot(){
    p_l_enemy tmp_l = list_enemy;

    while(tmp_l != NULL){
        if(tmp_l->kind == 2 || tmp_l->kind == 3)
            ((cattivo_f *)(tmp_l->data))->shoot(avatar->getY(), avatar->getX());

        tmp_l = tmp_l->next;
    }
}

//decrementa le vite dei personaggi
void funzioni::check_life(){
    check_enemy();

    check_M_caracter();
}

//decrementa la vita dei cattivi
void funzioni::check_enemy(){
    int i;
    bool check;
    p_l_enemy tmp = list_enemy;

    while(tmp != NULL){
        i = tmp->kind;

        if(i == 0){
            if(((cattivo *)(tmp->data))->getBeen_hit()){
                i = ((cattivo *)(tmp->data))->getAttack();
                ((cattivo *)(tmp->data))->resetBeen_hit();
                check = true;
            } else check = false;
        }
        else if(i == 1){
            if(((cattivo_r *)(tmp->data))->getBeen_hit()){
                i = ((cattivo_r *)(tmp->data))->getAttack();
                ((cattivo_r *)(tmp->data))->resetBeen_hit();
                check = true;
            } else check = false;
        }
        else if(i == 2 || i == 3){
            check_arrow_enemy(((cattivo_f *)(tmp->data)));

            if(((cattivo_f *)(tmp->data))->getBeen_hit()){
                i = ((cattivo_f *)(tmp->data))->getAttack();
                ((cattivo_f *)(tmp->data))->resetBeen_hit();
                check = true;
            } else check = false;
        }

        if(check){
            if(lifePlus){
                lifePlus = false;
                 wins->resetLifePlus();
            } else {
            avatar->decrese_life(i);
            wins->removeLife(i);
            }
        }

        tmp = tmp->next;
    }
}

//controlla che le frecce dei nemici abbiano colpito il protagonista
void funzioni::check_arrow_enemy(cattivo_f *p){
    list_arrow *tmp = p->getList();
    list_arrow *tmp_s = NULL;
    int i = p->getAttack();

    while (tmp != NULL){
        tmp_s = tmp->next;
        if(tmp->data->getDead()){
            if(tmp->data->getBeen_hit()){
                if(lifePlus){
                    lifePlus = false;
                    wins->resetLifePlus();
                } else {
                    avatar->decrese_life(i);
                    wins->removeLife(i);
                }
            }

            p->pop(tmp);
        }

        tmp = tmp_s;
    }
}

//controlla che il personaggio non sia stato colpito
void funzioni::check_M_caracter(){
    chtype tmp_c;
    bool out = false;
    p_l_enemy tmp_e = list_enemy;
    int i = 0;

    if(avatar->getBeen_hit()){
        tmp_c = avatar->getHit_by();
        avatar->resetBeen_hit();
        if(tmp_c == 'n')
            i = 0;
        else if(tmp_c == 'N')
            i = 1;
        else if(tmp_c == 'f' || tmp_c == 'F')
            i = 2;

        while(tmp_e != NULL && !out){
            if(tmp_e->kind == i)
                out = true;
            else tmp_e = tmp_e->next;
        }

        if(i == 0)
            i = ((cattivo *)(tmp_e->data))->getAttack();
        else if(i == 1)
            i = ((cattivo_r *)(tmp_e->data))->getAttack();
        else if(i == 2)
            i = ((cattivo_f *)(tmp_e->data))->getAttack();  
        
        
        if(lifePlus){
            lifePlus = false;
            wins->resetLifePlus();
        } else {
            avatar->decrese_life(i);
            wins->removeLife(i);
        }
    }
    
    check_arrow_main();
}

//controlla se le frecce del personaggio hanno colpito qulcosa
void funzioni::check_arrow_main(){
    list_arrow *l = avatar->getList();
    list_arrow *tmp = NULL;
    chtype c;

    while(l != NULL){
        tmp = l->next;
        if(l->data->getDead()){
            if(l->data->getBeen_hit()){
                c = l->data->getHit_by();
                if(c == 'n')
                    been_hit(0,l->data->getY(),l->data->getX());
                else if(c == 'N')
                    been_hit(1,l->data->getY(),l->data->getX());
                else if(c == 'f')
                    been_hit(2,l->data->getY(),l->data->getX());
                else if(c == 'F')
                    been_hit(3,l->data->getY(),l->data->getX());
            }

            avatar->pop(l);
        }

        l = tmp;
    }
}

//decrementa la vita ai cattivi e aggiunge punti al tabellone
void funzioni::been_hit(int i, int y, int x){
    p_l_enemy tmp = list_enemy;
    p_l_enemy final = NULL;

    while(tmp != NULL){
        if(tmp->kind == i){
            if(final == NULL)
               final = tmp;
            else final = closer(tmp, final, y, x);
        }

        tmp = tmp->next;
    }

    if(i == 0)
        ((cattivo *)(final->data))->decrese_life(avatar->getAttack());
    if(i == 1)
        ((cattivo_r *)(final->data))->decrese_life(avatar->getAttack());
    else ((cattivo_f *)(final->data))->decrese_life(avatar->getAttack());

    wins->addPoints(avatar->getAttack());
}

//trova il nemico più vicino alla freccia sparata
p_l_enemy funzioni::closer(p_l_enemy a, p_l_enemy b, int y, int x){
    p_l_enemy tmp = NULL;
    int valA = 0;
    int valB = 0;

    if(a->kind == 0){
        valA = abs(y-((cattivo *)(a->data))->getY())+abs(x-((cattivo *)(a->data))->getX());
        valB = abs(y-((cattivo *)(b->data))->getY())+abs(x-((cattivo *)(b->data))->getX());
    }
    else if(a->kind == 1){
        valA = abs(y-((cattivo_r *)(a->data))->getY())+abs(x-((cattivo_r *)(a->data))->getX());
        valB = abs(y-((cattivo_r *)(b->data))->getY())+abs(x-((cattivo_r *)(b->data))->getX());
    }
    else if(a->kind == 2 || a->kind == 3){
        valA = abs(y-((cattivo_f *)(a->data))->getY())+abs(x-((cattivo_f *)(a->data))->getX());
        valB = abs(y-((cattivo_f *)(b->data))->getY())+abs(x-((cattivo_f *)(b->data))->getX());
    }

    if(valA < valB)
        tmp = a;
    else tmp = b;

    return (tmp);
}

//prende la chiave e attiva la porta
void funzioni::f_key(){
    
    if(list_levels->room == 0){
        Key = map_one->delete_key();
    }
    else if(list_levels->room  == 1){
        Key = map_two->delete_key();
    }
    else {
        Key = map_three->delete_key();
    }
}

//estrae e attiva il potere
void funzioni::getAbility(){
    int tmp, i;

    if(list_levels->room == 0)
        tmp = map_one->ArtGenerator();
    else if(list_levels->room  == 1)
        tmp = map_two->ArtGenerator();
    else tmp = map_three->ArtGenerator();

    if(tmp == 0){
        i = (extract_random(3)+1)*5;
        if(avatar->getLife()+i > 30){
            wins->lifePlus();
            lifePlus = true;
        }
        avatar->add_life(i);
        wins->addLife(i);
    }
    else if(tmp == 1 && ability != 1){
        avatar->getFast();
        wins->addSpeed();
    }
    else if(tmp == 2 || (tmp == 1 && ability == 1)){
        wins->addArrows();
        avatar->getArrowFast();
        if(tmp == 1 && ability == 1) ability++;
    }

    ability = ability + tmp;
}

//prende l'artefatto
void funzioni::f_artifact(){

    if(list_levels->room == 0)
        artifact = map_one->delete_Art();
    else if(list_levels->room  == 1)
        artifact = map_two->delete_Art();
    else artifact = map_three->delete_Art();
}

//si sposta in una stanza precedente o successiva
void funzioni::move_door(bool prev){
    save_datas();

    posY = 0;
    posX = 0;

    if(!prev){
        if(list_levels->next == NULL)
            new_room();
        else list_levels = list_levels->next;
        forward = true;
    } else {
        forward = false;
        list_levels = list_levels->prev;
    }
    
    inizialize_map();
    if (forward) {
        wins->addMap();
    }
    else {
        wins->subMap();
    }

}

//salva i dati
void funzioni::save_datas(){
    if (list_levels ->key_b)
        f_key();

    if (list_levels->artifact)
        f_artifact();

    life_main = avatar->getLife();
    posX = avatar->getX();
    posY = avatar->getY();

    l_enemy *tmp = list_enemy;

    while(tmp != NULL){
        list_enemy = list_enemy->next;
        switch(list_levels -> room){
            case 0:
                list_levels->Enemy[tmp->position] = map_one->delete_enemy(tmp->position, tmp->kind);
                break;
            case 1:
                list_levels->Enemy[tmp->position] = map_two->delete_enemy(tmp->position, tmp->kind);
                break;
            case 2:
                list_levels->Enemy[tmp->position] = map_three->delete_enemy(tmp->position, tmp->kind);
                break;
        }
        tmp = list_enemy;
    }

    switch(list_levels -> room){
        case 0:
            avatar = map_one->deleteMain();
            wrefresh(W);
            delete map_one;
            map_one = NULL;
            break;
        case 1:
            avatar = map_two->deleteMain();
            wrefresh(W);
            delete map_two;
            map_two = NULL;
            break;
        case 2:
            avatar = map_three->deleteMain();
            wrefresh(W);
            delete map_three;
            map_three = NULL;
            break;
    } 
}

//estrae a sorte un numero da 0 a max-1
int funzioni::extract_random(int max){
    int tmp = rand() % max;
    return (tmp);
}

//riavvia o termina il gioco perchè il personaggio è morto
void funzioni::End(){
    menuEnd *menuE = new menuEnd(W);
    int tmp = 1;
    check_game = false;
    save_datas();

    while (tmp == 1){
        menuE->startMenu();
        tmp = menuE->getResult();

        switch(tmp){
            case 0:
                life_main = 30;
                posY = 0;
                posX = 0;
                cleanMemory();
                forward = true;
                wins->resetCount();
                wins->inizializeWindows();
                ability = 0;
                lifePlus = false;
                break;
            case 1:
                menuE->instructions();
                break;
            case 2:
                check_end = false;
                break;
        }
    }
    delete menuE;
}

//avvia il menu di inizio
void funzioni::menuStart(){
    menu *tmp_M = new menu(W);

    int ris = 1;
    while (ris == 1){
        tmp_M -> startMenu();
        ris = tmp_M->getResult();

        switch(ris){
            case 0:
                check_end = true;
                break;
            case 1:
                tmp_M->instructions();
                break;
            case 2:
                check_end = false;
                break;
        }
    }
    delete tmp_M;
}

//menu pausa
void funzioni::time_out(){
    save_datas();
    int tmp;
    menuPause *Menu = new menuPause(W);

    
    Menu->startMenu();
    tmp = Menu->getResult();
    delete Menu;

    if(tmp == 0)
        inizialize_map();
    else if(tmp == 1){
        cleanMemory();
        life_main = 30;
        check_game = false;
        posY = 0;
        posX = 0;
        forward = true;
        wins->resetCount();
        wins->inizializeWindows();
        ability = 0;
        lifePlus = false;
    } else {
        check_game = false;
        check_end = false;
    }
}

void funzioni::cleanMemory(){
    p_level tmp = list_levels;
    p_level tmp_s = NULL;

    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    while(tmp->prev != NULL){
        tmp_s = tmp;
        tmp = tmp->prev;
        delete tmp_s;
    }
    delete tmp;
    list_levels = NULL;
}