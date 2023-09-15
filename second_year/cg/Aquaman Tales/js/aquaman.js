/*-------------------------------------------------------------------------------------------------------------------------*\
|                                        _____     _                    __                                                  |
|                                       |_   _|_ _| | ___  ___    ___  / _|                                                 |
|                                         | |/ _` | |/ _ \/ __|  / _ \| |_                                                  |
|                                         | | (_| | |  __/\__ \ | (_) |  _|                                                 |
|                                         |_|\__,_|_|\___||___/  \___/|_|                                                   |
|                                                                                                                           |
|                                           _                                                                               |
|                                          / \   __ _ _   _  __ _ _ __ ___   __ _ _ __                                      |
|                                         / _ \ / _` | | | |/ _` | '_ ` _ \ / _` | '_ \                                     |
|                                        / ___ \ (_| | |_| | (_| | | | | | | (_| | | | |                                    |
|                                       /_/   \_\__, |\__,_|\__,_|_| |_| |_|\__,_|_| |_|                                    |
|                                                  |_|                                                                      |
|                                                                                                                           |
|                                                                                                                           |
|                                                                   ________________________________________________________|
|                                                                  | => Trabalho elaborado por João Rodrigo Condeço nº48976 |
|                                                                  |    Curso de Engenharia Informática                     |
|                                                                  |    Universidade de Évora                               |
\*-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------| Desenhos |------------------------------------------------------*/
/*------------------*\
| Desenho do Aquaman |
\*------------------*/
function generateAquaman() {
    this.lineWidth = 0.004;
    /*---------------------------------------------------------------------*/
    //Fin

    this.fillStyle = "orange";
    this.beginPath();
    this.moveTo(-0.2, 0);
    this.quadraticCurveTo(-0.1, 0.2, -0.1, 0.5);
    this.quadraticCurveTo(-0.2, 0.55, -0.24, 0.44);
    this.lineTo(-0.32, 0.52);
    this.quadraticCurveTo(0.1, 0.8, 0.1, 0.5);
    this.quadraticCurveTo(0.1, 0.2, 0.2, 0.0);
    this.lineTo(-0.2, 0);
    this.fill();
    this.stroke();

    this.beginPath();
    this.moveTo(-0.24, 0.44);
    this.quadraticCurveTo(-0.18, 0.34, -0.22, 0.28);
    this.quadraticCurveTo(-0.25, 0.39, -0.3, 0.4);
    this.quadraticCurveTo(-0.31, 0.43, -0.35, 0.45);
    this.quadraticCurveTo(-0.36, 0.49, -0.4, 0.5);
    this.quadraticCurveTo(-0.42, 0.53, -0.47, 0.50);
    this.quadraticCurveTo(-0.40, 0.59, -0.32, 0.52);
    this.lineTo(-0.24, 0.44);
    this.fill();


    /*---------------------------------------------------------------------*/
    //upper body


    this.fillStyle = "#f2dca0"
    this.beginPath();
    this.moveTo(-0.2, 0);
    this.quadraticCurveTo(-0.16, -0.20, -0.1593, -0.30);
    this.lineTo(-0.16, -0.48);
    this.lineTo(-0.07934, -0.47863);
    this.quadraticCurveTo(-0.039, -0.48, -0.04, -0.516);
    this.lineTo(0.04, -0.516);
    this.quadraticCurveTo(0.038, -0.48, 0.07934, -0.47863);
    this.lineTo(0.16, -0.48);
    this.lineTo(0.1593, -0.30);
    this.quadraticCurveTo(0.16, -0.20, 0.2, 0);
    this.fill();
    this.stroke();

    //abs
    this.beginPath();
    for (let i = -0.20; i < -0.1; i += 0.025) {
        for (let j = 0; j <= 0.1; j += 0.1) {
            this.moveTo((-0.1 + j), i);
            this.quadraticCurveTo((-0.049 + j), (i + 0.021), (0 + j), i);
        }
    }
    this.stroke();



    /*---------------------------------------------------------------------*/

    //head
    this.beginPath();
    this.arc(0, -0.59, 0.1, 0, 2 * Math.PI);
    this.fill();
    this.stroke();

    /*---------------------------------------------------------------------*/

    //left arm
    this.beginPath();
    this.moveTo(-0.16, -0.48);
    this.lineTo(-0.32003, -0.33759);
    this.quadraticCurveTo(-0.341, -0.29726, -0.32325, -0.26177);
    this.lineTo(0.0155, -0.15692);
    this.lineTo(0.038, -0.200);
    this.lineTo(-0.25873, -0.29887);
    this.lineTo(-0.16, -0.4);
    this.fill();
    this.stroke();




    //right arm
    this.beginPath();
    this.moveTo(0.16, -0.48);
    this.lineTo(0.4, -0.3);
    this.lineTo(0.65, -0.2);
    this.lineTo(0.6, -0.15);
    this.lineTo(0.36, -0.24);
    this.quadraticCurveTo(0.35, -0.24, 0.35, -0.25);
    this.lineTo(0.16, -0.402);
    this.fill();
    this.stroke();

    //right hand
    this.beginPath();
    this.moveTo(0.65, -0.2);
    this.lineTo(0.68842, -0.1737);
    this.lineTo(0.72569, -0.1718);
    this.lineTo(0.7256, -0.16)
    this.lineTo(0.61, -0.16)
    for (let i = 0; i < 3; i++) {
        let factor = i * 0.025
        this.rect(0.66 + factor, -0.109, 0.01, 0.01);
    }
    this.fill();
    this.stroke();

    /*---------------------------------------------------------------------*/
    //trident


    this.fillStyle = "#ffd966"

    this.beginPath();
    this.moveTo(-0.5, -0.16);
    this.lineTo(-0.5, -0.12);
    this.lineTo(0.8, -0.12);
    this.lineTo(0.80, -0.16);
    this.fill();
    this.stroke();

    let storedTransform = this.getTransform();

    this.scale(2, 2);
    this.translate(-0.4, 0.073);
    //Ponta
    this.beginPath();
    this.moveTo(0.80, -0.16);
    this.quadraticCurveTo(0.8, -0.18, 0.82, -0.2);
    this.lineTo(0.92, -0.2);
    this.lineTo(0.94, -0.192);
    this.lineTo(0.92, -0.18);
    this.lineTo(0.836, -0.184);
    this.quadraticCurveTo(0.816, -0.176, 0.816, -0.160);
    this.lineTo(0.820, -0.148);
    this.lineTo(0.959, -0.148);
    this.lineTo(0.98, -0.14);
    this.lineTo(0.959, -0.131);
    this.lineTo(0.820, -0.132);
    this.lineTo(0.815, -0.120);
    this.quadraticCurveTo(0.816, -0.104, 0.836, -0.096);
    this.lineTo(0.920, -0.096);
    this.lineTo(0.940, -0.088);
    this.lineTo(0.920, -0.080);
    this.lineTo(0.82, -0.08);
    this.quadraticCurveTo(0.800, -0.100, 0.800, -0.117)
    this.fill();
    this.stroke();

    this.setTransform(storedTransform);

    //left hand
    this.fillStyle = "#f2dca0"
    this.beginPath();
    this.moveTo(0.038, -0.200);
    this.lineTo(0.071, -0.178);
    this.lineTo(0.092, -0.16);
    this.lineTo(0.129, -0.156);
    this.lineTo(0.128, -0.146);
    this.lineTo(0.094, -0.144);
    this.lineTo(0.099, -0.112);
    this.lineTo(0.087, -0.111);
    this.lineTo(0.08, -0.14);
    this.lineTo(0.081, -0.111);
    this.lineTo(0.070, -0.110);
    this.lineTo(0.067, -0.139);
    this.lineTo(0.06, -0.14);
    this.lineTo(0.061, -0.112);
    this.lineTo(0.050, -0.110);
    this.lineTo(0.050, -0.110)
    this.lineTo(0.04, -0.14);
    this.lineTo(0.0155, -0.157);
    this.fill();
    this.stroke();

    /*---------------------------------------------------------------------*/
    //face

    //mouth
    this.fillStyle = "white";
    this.beginPath();
    this.moveTo(-0.04, -0.54);
    this.lineTo(-0.06, -0.58);
    this.lineTo(0.06, -0.58);
    this.lineTo(0.04, -0.54);
    this.stroke();
    this.fill();

    //eyes
    this.beginPath();
    this.arc(-0.04, -0.62, 0.02, 0, 2 * Math.PI);
    this.fill();
    this.stroke();
    this.beginPath();
    this.arc(0.04, -0.62, 0.02, 0, 2 * Math.PI);
    this.fill();
    this.stroke();

    this.fillStyle = "black";
    this.beginPath();
    this.arc(-0.033, -0.62, 0.01, 0, 2 * Math.PI);
    this.fill();
    this.stroke();
    this.beginPath();
    this.arc(0.047, -0.62, 0.01, 0, 2 * Math.PI);
    this.fill();
    this.stroke();

    //eyebrows
    this.beginPath();
    this.moveTo(-0.060, -0.648);
    this.lineTo(-0.057, -0.644);
    this.lineTo(-0.020, -0.636);
    this.lineTo(-0.024, -0.640);
    this.moveTo(0.060, -0.648);
    this.lineTo(0.057, -0.644);
    this.lineTo(0.020, -0.636);
    this.lineTo(0.024, -0.640);
    this.fill();


}

/*------------------*\
| Desenho dos Peixes |
\*------------------*/
function generateEnemy() {
    this.lineWidth = 0.004;
    this.fillStyle = "#0015ff";

    //upper fin
    this.beginPath();
    this.fill();
    this.moveTo(-1.004, -1.811);
    this.lineTo(1.109, -3.047);
    this.lineTo(1.004, -1.27)
    this.stroke();
    this.fill();

    //back fin
    this.beginPath();
    this.moveTo(3, -1);
    this.quadraticCurveTo(4.415, -1.401, 5, -2);
    this.quadraticCurveTo(4.8, 0, 5, 2);
    this.quadraticCurveTo(4.415, 1.401, 3, 1);
    this.fill();
    this.stroke();


    this.fillStyle = "#00aeff";

    //body
    this.beginPath();
    this.moveTo(-1.003, -1.824);
    this.lineTo(3, -1);
    this.lineTo(3, 1);
    this.lineTo(-1.003, 1.824);
    this.fill();
    this.stroke();

    this.fillStyle = "#0015ff";

    //inside fin
    this.beginPath();
    this.moveTo(0, -0.4);
    this.quadraticCurveTo(0.798, -0.488, 1.2, -0.8);
    this.quadraticCurveTo(1.0, 0, 1.2, 0.8);
    this.quadraticCurveTo(0.798, 0.488, 0, 0.4);
    this.fill();
    this.stroke();

    //head
    this.beginPath();
    this.moveTo(-1.003, -1.811);
    this.quadraticCurveTo(-2, -1.5, -2.5, -1);
    this.lineTo(-3, -0.2);
    this.lineTo(-3, 0.2);
    this.lineTo(-2.5, 1);
    this.quadraticCurveTo(-2, 1.5, -0.995, 1.8);
    this.fill();
    this.stroke();

    //mouth
    this.fillStyle = "#96e7ff";
    this.beginPath()
    this.moveTo(-3, -0.2);
    this.lineTo(-3, 0.2);
    this.lineTo(-3.1, 0.2);
    this.lineTo(-3.1, -0.2);
    this.fill();
    this.stroke();

    //eyes

    this.fillStyle = "white";
    this.beginPath();
    this.arc(-1.732, -0.785, 0.3, 0, 2 * Math.PI);
    this.fill();
    this.stroke();
    this.fillStyle = "black";
    this.beginPath();
    this.arc(-1.732, -0.785, 0.2, 0, 2 * Math.PI);
    this.fill();
    this.stroke();

}

/*-------------------------------*\
| Desenho dos disparos de energia |
\*-------------------------------*/
function generateEnergyBall() {
    let colors = ["#fff9b8", "#fff585", "#ffef47", "#ffea00"];
    let i = 0;

    for (let c in colors) {
        this.fillStyle = colors[c];
        this.beginPath();
        this.arc(150, 150, (50 - i), 0, 2 * Math.PI);
        this.moveTo(140, (200 - i));
        this.lineTo((70 + i), 150);
        this.lineTo((140 + i), (100 + i));
        this.fill();
        i += 10;
    }

}

/*------------------*\
|  Ecrã de derrota   |
\*------------------*/
function gameOver() {
    this.globalAlpha = 0.7;
    this.fillStyle = "black";
    //this.font = '50px serif';
    this.fillRect(0, 0, 1000, 600);
    //this.fillText("Game Over", 500, 300);
}

/*-------------------*\
| Vidas do personagem |
\*-------------------*/
function showLifes(n) {
    this.lineWidth = 0.004;
    this.fillStyle = "black";
    this.fillRect(-0.1, -0.1, 0.8, 0.3);

    this.fillStyle = "red";

    for (let i = 0; i < n; i++) {
        let factor = 0.15 * i;
        this.beginPath();
        this.moveTo(0 + factor, 0.13);
        this.quadraticCurveTo(0.080 + factor, 0.060, 0.07 + factor, 0);
        this.quadraticCurveTo(0.05 + factor, -0.05, 0 + factor, 0);
        this.quadraticCurveTo(-0.05 + factor, -0.05, -0.07 + factor, 0);
        this.quadraticCurveTo(-0.080 + factor, 0.060, 0 + factor, 0.13)
        this.fill();
        this.stroke();
    }

}

/*------------------*\
|  Barra de energia  |
\*------------------*/
function charge(n) {
    this.lineWidth = 0.004;
    this.fillStyle = "black";
    this.fillRect(-0.1, -0.1, 0.8, 0.3);


    this.fillStyle = "#00ff84";
    this.fillRect(-0.07, -0.05, (0.5 * n), 0.2);
}


function message(text) {
    let terminal = document.getElementById("terminal");
    terminal.innerHTML = text;
}

function message2(text) {
    let terminal = document.getElementById("terminal2");
    terminal.innerHTML = text;
    terminal.style.visibility = "visible";
}

function restart() {
    if (confirm("Tem a certeza que deseja reiniciar?")) {
        window.location.reload();
    }
}


function enter_ref(dx, dy, sx, sy, a) {
    this.save();
    this.translate(dx, dy);
    this.rotate(a);
    //this.translate(0,0);
    this.scale(sx, sy);
    //this.translate(dx, dy);
}

function leave_ref() { this.restore(); }

/*-------------------------------------------------------| Criar Personagens |------------------------------------------------------*/
function render(model) {

    let aquaman = model.aquaman;
    let enemyList = model.enemies.list;
    let hearts = model.heart;
    let dishoomList = model.dishooms.list;
    let charge = model.loading;
    //
    message(`Points: ${Math.round(model.elapsed_time / 1000)}<br>Enemies <br>killed: ${model.aquaman.points} <br>Lifes: ${model.aquaman.lives}<br>Age: ${model.age}<br><br>Prima L<br>para<br>disparar`);

    //Referencial do modelo
    this.enter_ref(0, 0, this.canvas.width, this.canvas.height, 0);

    //Background
    this.fillStyle = "#66faff";
    this.fillRect(0, 0, 1, 1);

    //Personagem principal
    this.enter_ref(aquaman.x, aquaman.y, aquaman.sizeX, aquaman.sizeY, 0);
    this.getAquaman();
    this.leave_ref();

    //Inimigos (peixes)
    for (let i in enemyList) {
        let target = enemyList[i];
        this.enter_ref(target.x, target.y, target.size, target.size);
        this.getEnemy();
        this.leave_ref();
    }

    //Disparos de energia
    for (let i in dishoomList) {
        let target = dishoomList[i];
        this.enter_ref(target.x, target.y, target.size, target.size);
        this.getDishooms();
        this.leave_ref();
    }

    //Vidas
    this.enter_ref(hearts.x, hearts.y, hearts.size, hearts.size, 0);
    this.getLifes(aquaman.lives);
    this.leave_ref();

    //Mensagem de gameover
    if (model.gameover) {
        this.gameOver();
        message2("GAME OVER");
    }
    else {
        message2("");
    }

    if (model.paused) {
        this.gameOver();
    }

    //Barra de energia
    this.enter_ref(charge.x, charge.y, hearts.size, hearts.size, 0);
    this.charge(charge.charged);
    this.leave_ref();

    this.leave_ref();
}


/*-------------------------------------------------------------------------------------------------------------------------*\
| A função fishCreator tem como objetivo criar vários objetos com a caracteristica do objeto "fishes", declarado na mesma,  |
| mas em posições aleatórias diferentes. A velocidade com que estes objetos são criados aumenta com o aumento da pontuação  |
| para dificultar ao jogador e o jogo não ser tão simples.                                                                  |
| É guardado no modelo um "index" imaginário do objeto para facilitar a sua remoção da lista quando necessário.             |
| Os objetos são guardados numa lista para, na função render, serem "desenhados".                                           |
\*-------------------------------------------------------------------------------------------------------------------------*/
function enemyCreator(points, fishList) {

    let fishes = {
        x: 0.5,
        y: 0.5,
        vx: 0.005,
        vy: 0.01,
        size: 0.01,
        id: (fishList.lastId + 1),
        alive: true,
    }

    if (fishList.current > (fishList.previous + 100)) {

        fishes.y = Math.random((0.7 - 0.2) + 0.2);
        fishes.x = 1 + (fishes.size * 5);
        fishList.list.push(fishes);
        fishList.previous = fishList.current;
        fishList.lastId++;
    }
    fishList.current += (1 + (points * 0.1));
}


/*-------------------------------------------------------------------------------------------------------------------------*\
| A função dishoomCreator segue a mesma lógica da função fishCreator mas para os disparos de energia.                       |
| As diferenças mais significativas são o facto desta não variar com o tempo e as suas posições não serem aleatórias        |
\*-------------------------------------------------------------------------------------------------------------------------*/
function dishoomCreator(dishoomList, aquaman) {
    let dishooms = {
        x: aquaman.x + 0.105,
        y: aquaman.y - 0.095,
        vx: 0.01,
        vy: 0,
        id: (dishoomList.lastId + 1),
        visible: true,
        size: 0.0005,
    }
    dishoomList.list.push(dishooms);
    dishoomList.lastId++;
}

/*-------------------------------------------------------------------------------------------------------------------------*\
| A função fishHandler é responsável por:                                                                                   |
|   => Verificar se o peixe colide com o personagem ou com os disparos de energia                                           |
|   => Caso isto se verifique alterar a velocidade do mesmo de forma a este descer para baixo                               |
|   => Se o peixe passar dos limites do ecrã elimina-o                                                                      |
|   => Se o peixe tiver passado a área defendida pelo Aquaman uma vida é perdida                                            |
\*-------------------------------------------------------------------------------------------------------------------------*/
function enemyHandler(enemy, aquaman, list, dishoomList) {

    let restartPoint = 0 - (enemy.size * 5);// Ponto onde será descontada uma vida ao jogador

    let xDeath = aquaman.x + 0.1;           // Ponto de colisão com o personagem (x máximo)
    let xDeathMin = aquaman.x - 0.1;        // Ponto de colisão com o personagem (x minimo)
    let yDeathMax = aquaman.y + 0.08;       // Ponto de colisão com o personagem (y máximo)
    let yDeathMin = aquaman.y - 0.08;       // Ponto de colisão com o personagem (y minimo)
    let gotHit = false;

    // Ciclo que verifica se as coordenadas do peixe coincidem com as coordenadas de algum dos disparos de energia
    for (let i in dishoomList) {
        let x = dishoomList[i].x;
        let y = dishoomList[i].y;
        if ((enemy.x > (x - 0.04) && enemy.x < (x + 0.1)) && (enemy.y > (y - 0.08) && enemy.y < (y + 0.08))) {
            gotHit = true;                                                                              //Se coincidir será registado
        }
    }


    //Apagar personagem
    if (enemy.x < restartPoint) {                                                    // => Se ultrapassar os limites horizontais do ecrã
        for (let i in list) {
            if (list[i].id == enemy.id) {                                             // => Procura o peixe através do "index imaginário" atribuido ao mesmo
                list.splice(list.indexOf(list[i]), list.indexOf(list[i]) + 1);     //    e elimina-o da lista
            }
        }
        aquaman.lives -= 1;                                                         // => Como neste caso o mesmo conseguiu ultrapassar o objetivo uma 
    }                                                                               //    vida é retirada
    else if ((enemy.y > 1.2)) {                                                       // => Se morrer e ultrapassar os limites verticais do ecrã o mesmo
        for (let i in list) {                                                         //    será feito (excluindo a remoção de uma vida, neste caso um ponto
            if (list[i].id == enemy.id) {                                             //    é adicionado).
                list.splice(list.indexOf(list[i]), list.indexOf(list[i]) + 1);
            }
        }
        aquaman.points += 1;
    }
    else if (((enemy.x >= xDeathMin && enemy.x <= xDeath) && (enemy.y >= yDeathMin && enemy.y <= yDeathMax)) || (gotHit)) {       // => Se for atingido pelas energy balls
        enemy.vx = 0;                                                                                                           //    ou atingido pelo aquaman, o inimigo 
        enemy.vy = 0.02;                                                                                                        //    deixa de ser considerado vivo e o seu movimento
        enemy.alive = false;                                                                                                    //    passa a ser para baixo para ser eliminado.
    }


    if ((enemy.y > 0.95 || enemy.y < 0.05) && enemy.alive) {                          // => Define o espaço em que os peixes se movimentam
        enemy.vy *= -1;
    }


    enemy.y += enemy.vy;                                                            // As suas posições são atualizadas
    enemy.x -= enemy.vx;
}


/*-------------------------------------------------------------------------------------------------------------------------*\
| A função dishoomHandler atualiza as posições dos disparos de energia e, caso estes ultrapassem os limites do mapa,        |
| elimina-os da lista.                                                                                                      |
\*-------------------------------------------------------------------------------------------------------------------------*/
function dishoomHandler(dishoom) {
    let list = dishoom.list;
    for (let i in list) {
        if (list[i].x > 1.1) {
            list.splice(list.indexOf(list[i]), list.indexOf(list[i]) + 1);
        }
        else {
            list[i].x += list[i].vx;
        }
    }

    for (let j in dishoom.xList) {
        dishoom.xList[j] += 0.01;
    }
}

function update() {

    //----------------------------------------------| Setup |----------------------------------------------\\
    let aquaman = this.aquaman;
    let fishList = this.enemies;
    let dishoomList = this.dishooms;
    let list = fishList.list;
    let charge = this.loading;

    if (aquaman.lives <= 0) {             // => Verifica se o jogo terminou
        this.gameover = true;
        return;
    }
    else if (this.paused) return;       // => Verifica se o jogo está na pausa

    this.age += 1;


    //----------------------------------------------| Aquaman |----------------------------------------------\\
    switch (aquaman.action) {                                                               // => Controlos de movimento do Aquaman
        case 1: /* UP */ aquaman.y -= aquaman.vy; break;
        case 2: /* DOWN */ aquaman.y += aquaman.vy; break;
        case 3: /* RIGHT */ aquaman.x += aquaman.vx; break;
        case 4: /* LEFT */ aquaman.x -= aquaman.vx; break;
        case 5: /* UP RIGHT */ aquaman.y -= aquaman.vy; aquaman.x += aquaman.vx; break;
        case 6: /* UP LEFT */ aquaman.y -= aquaman.vy; aquaman.x -= aquaman.vx; break;
        case 7: /* DOWN RIGHT */ aquaman.y += aquaman.vy; aquaman.x += aquaman.vx; break;
        case 8: /* DOWN LEFT */ aquaman.y += aquaman.vy; aquaman.x -= aquaman.vx; break;
        default: break;
    }

    //----------------------------------------------| Disparos de Energia |----------------------------------------------\\

    if (charge.charged < 1.48) {                         // => Verifica se está pronto para disparar   
        charge.charged += charge.vcharge;              //     (*) Se não tiver continua a carregar
    }
    else {
        charge.ready = true;                           //     (*) Se tiver regista que está pronto
    }

    if (aquaman.dishoom && charge.ready) {               // => Verifica que tá pronto para disparar e foi pedido
        dishoomCreator(dishoomList, aquaman);          // => Função que cria os disparos
        this.audio.currentTime = 0.20;
        this.audio.play();                             // => Som decorativo (A melhorar)
        charge.ready = false;
        charge.charged = 0;                            // => Reinicia o carregamento 
    }
    aquaman.dishoom = false;                           // => Pára a sequência de disparos

    dishoomHandler(dishoomList);                       // => Função que lida com a eliminação e movimento dos disparos

    //----------------------------------------------| Peixes |----------------------------------------------\\

    enemyCreator(aquaman.points, fishList);                      // => Função que gera peixes aleatórios

    for (let i in list) {                                         // => Peixes existentes na lista de objetos são criados nas 
        enemyHandler(list[i], aquaman, list, dishoomList.list);  //    devidas posições e atualizados através da função fishHandler.
    }

}

function new_model(lifes) {
    let model = {
        age: 0,
        gameover: false,
        elapsed_time: 0,
        paused: false,
        audio: new Audio("media/DISHOOM.mp3"),        //Som dos disparos

        aquaman: {
            x: 0.5,
            y: 0.5,
            vx: 0.008,
            vy: 0.008,
            sizeX: 0.12,
            sizeY: 0.15,
            action: 0,
            lives: lifes,
            points: 0,
            deathPoint: -1000,
            dishoom: false,
        },

        dishooms: {
            previous: 5,
            current: 5,
            list: [],
            lastId: -1,
        },

        genericEnemy: {
            x: 0.5,
            y: 0.5,
            vx: 0.005,
            vy: 0.01,
            size: 0.02,
            alive: true,
            id: -1,
        },

        enemies: {
            objectiveX: 0,
            previous: 5,
            current: 5,
            list: [],
            lastId: -1,
        },

        heart: {
            x: 0.85,
            y: 0.04,
            size: 0.2,
            previous: 5,
            //rodar quando diminuir
        },

        keys: {
            wP: false,
            dP: false,
            aP: false,
            sP: false,
            lP: false,
        },

        loading: {
            x: 0.85,
            y: 0.11,
            charged: 0,
            vcharge: 0.01,
            ready: false,
        }

    };
    model.update = update;


    // Para o movimento do personagem ser mais fluido decidi alterar o estado do personagem em função das teclas levantadas
    // Assim o movimento é iniciado quando uma tecla é premida mas apenas será alterado quando as mesmas forem levantadas
    // Anteriormente apenas tinha quando as teclas eram premidas mas o movimento do personagem era muito lento.

    let wP = model.keys.wP;
    let dP = model.keys.dP;
    let aP = model.keys.aP;
    let sP = model.keys.sP;

    document.addEventListener("keydown", (e) => {
        switch (e.key) {
            case "w": case "W": wP = true; break;
            case "s": case "S": sP = true; break;
            case "d": case "D": dP = true; break;
            case "a": case "A": aP = true; break;
            default: model.aquaman.action = 0; break;
        }

        if (wP && dP) model.aquaman.action = 5;
        else if (wP && aP) model.aquaman.action = 6;
        else if (sP && dP) model.aquaman.action = 7;
        else if (sP && aP) model.aquaman.action = 8;
        else if (wP) model.aquaman.action = 1;
        else if (sP) model.aquaman.action = 2;
        else if (dP) model.aquaman.action = 3;
        else if (aP) model.aquaman.action = 4;

    });

    document.addEventListener("keydown", (e) => {
        switch (e.key) {
            case "l": case "L": model.aquaman.dishoom = true; break;
            case " ": model.paused = !model.paused; break;
            default: model.aquaman.dishoom = false;
        }
    });


    document.addEventListener("keyup", (e) => {
        switch (e.key) {
            case "w": case "W": wP = false; break;
            case "d": case "D": dP = false; break;
            case "a": case "A": aP = false; break;
            case "s": case "S": sP = false; break;
        }
        //if(!wP || !sP || !dP || !aP) model.aquaman.action = 0;

        if (wP && dP) model.aquaman.action = 5;
        else if (wP && aP) model.aquaman.action = 6;
        else if (sP && dP) model.aquaman.action = 7;
        else if (sP && aP) model.aquaman.action = 8;
        else if (wP) model.aquaman.action = 1;
        else if (sP) model.aquaman.action = 2;
        else if (dP) model.aquaman.action = 3;
        else if (aP) model.aquaman.action = 4;
        else if (!(wP || sP || dP || aP)) model.aquaman.action = 0;
    });

    return model;
}


function main() {
    let gc = document.getElementById("canvas").getContext("2d");
    gc.canvas.width = 1200;
    gc.canvas.height = 650;

    gc.render = render;
    gc.enter_ref = enter_ref;
    gc.leave_ref = leave_ref;

    gc.getAquaman = generateAquaman;
    gc.getEnemy = generateEnemy;
    gc.getLifes = showLifes;
    gc.gameOver = gameOver;
    gc.getDishooms = generateEnergyBall;
    gc.charge = charge;

    let model = new_model(5);
    let step = (ts) => {
        gc.render(model);
        if (!model.paused && !model.gameover) model.elapsed_time = ts;
        model.update();
        requestAnimationFrame(step);
    }
    requestAnimationFrame(step);
}


/* Erros por corrigir e dificuldades:

    => Alguns peixes desaparecem inesperadamente quando se acumulam muitos.

    => Melhorar a precisão da posição em que o peixe deve morrer.

    => Melhorar o som do disparo.
*/


/* IDEIAS

    => juntar ondinhas a sair atrás dos peixes (o x seria o x do peixe + qualquer valor) 

    => o y do peixe foge do y do jogador                                

    => velocidade dos peixes vai aumentando com o número de pontos   ->| DONE |<-

    => barra de vidas ultima cena desenhada    ->| DONE |<-

    => Mensagem de game over    ->| DONE |<-
*/