function message(text) {
    let terminal = document.getElementById("terminal");
    terminal.innerHTML = text;
}
/**
 * MODEL
 */

function new_model() {
    let model = {
        age: 0,
        angle: 0.0,
        angle_step: 0.01 * Math.PI,

        iceRing:{
            limitX: 4.01,
            limitZ: 4.01,
            jumpRadius: 0.2,
        },

        dancer:{
            x: 0,
            y: 0.79,
            z: 0,
            vx: 0.03,
            vy: 0,
            vz: 0.02,
            radius: 1,
            angle: 0.0,
            angle_step: 0.01 * Math.PI
        },

        buidlings:{
            x: 0,
            y: 20,
            z: 0,
            vy: -0.3
        },

        background:{
            x: 0,
            y: -8,
            z: 0,
            vx: 0,
            vy: 0.1,
            vz: 0,
            angle: 0.0,
            angle_step: 0.03*Math.PI,
            scale: 0.1,
            vscale: 0.1
        }
    }

    model.update = update;

    return model;
}

function distance(point){
    return Math.sqrt(Math.pow(point.x - 0, 2) + Math.pow(point.z - 0, 2))
}


function update() {
    let dancer = this.dancer;
    let iceRing = this.iceRing;
    let buidlings = this.buidlings;
    let background = this.background;

    
    /*----------------------------------------------------------|Dancers|----------------------------------------------------------*/
    
    /*--------------------| Limits |----------------------*/
    if(((dancer.x + dancer.radius) > iceRing.limitX) || ((dancer.x - dancer.radius) < -iceRing.limitX)){
        dancer.vx *= -1;
    }
    
    if(((dancer.z - dancer.radius) < -iceRing.limitZ)||((dancer.z + dancer.radius) > iceRing.limitZ)){
        dancer.vz *= -1;
    }

    /*--------------------| Jump |----------------------*/
    
    if(dancer.y > 1.4){
        dancer.vy *= -1;
    }
    else if(dancer.y <= 0.79){
        dancer.vy = 0;
    }

    if((this.age % 333 == 0) && dancer.vy == 0){
        dancer.vy = 0.01;
    }

    if(dancer.vy != 0){  
        dancer.angle_step = 0.05 * Math.PI;
    }
    else{
        dancer.angle_step = 0.01 * Math.PI;
    }

    dancer.x += dancer.vx;
    dancer.y += dancer.vy;
    dancer.z += dancer.vz;
    this.age += 1; 


    dancer.angle += dancer.angle_step;

    /*----------------------------------------------------------|City|----------------------------------------------------------*/
    if(buidlings.y > -1) buidlings.y += buidlings.vy

    if(background.y < -1){
        background.y += background.vy
        background.angle += background.angle_step;
    }
    else if(background.angle > (0)){
        background.angle = 0;
    }
    if(background.scale < 1) background.scale += background.vscale
    
    //while(background.angle % 6.28318531 != 0){
    //    background.angle += background.angle_step;
    //}




}
/**
 * CONTEXT
 */
function new_context() {
    let cityBuildings = document.getElementById("cityBuildings");
    let background = document.getElementById("ground");
    let dancers = document.getElementById("dancers");
    let camera = document.getElementById("follow");

    let context = {
        cityBuildings: cityBuildings,
        background: background,
        dancers: dancers,
        camera: camera,
    };

    context.render = render;

    return context;
}   

function render(model) {
    message(`AGE: ${model.age}`);
    this.dancers.setAttribute(
        "rotation", `0 1 0 ${model.dancer.angle}`);

    this.dancers.setAttribute(
        "translation", `${model.dancer.x} ${model.dancer.y} ${model.dancer.z}`); 
    
    /*------------| background |--------------*/
    
    this.background.setAttribute(
        "scale", `${model.background.scale} ${model.background.scale} ${model.background.scale}`);

    this.background.setAttribute(
        "rotation", `0 1 0 ${model.background.angle}`);

    this.background.setAttribute(
        "translation", `0 ${model.background.y} 0`);
    
    
    /*------------| Buildings |--------------*/
    this.cityBuildings.setAttribute(
        "translation", `${model.buidlings.x} ${model.buidlings.y} ${model.buidlings.z}`); 


    /*------------| Camera |--------------*/
    this.camera.setAttribute(
        "position", `${model.dancer.x} ${model.dancer.y + 2.5}  ${model.dancer.z + 5} `);

}

/*
*   MAIN
*/
function main() {
    message("I'm Alive.");

    let gc = new_context();
    let model = new_model();

    let step = (ts) => {
        model.update();
        gc.render(model);
        requestAnimationFrame(step);
    }
    requestAnimationFrame(step);
}



//Botões
function changeColor1(){
    let btn1 = document.getElementById("button1");
    let btn2 = document.getElementById("button2");

    btn1.style.backgroundColor = "rgb(255, 255, 255)";
    btn2.style.backgroundColor = "rgb(54, 255, 111)";
}

function changeColor2(){
    let btn1 = document.getElementById("button1");
    let btn2 = document.getElementById("button2");

    btn2.style.backgroundColor = "rgb(255, 255, 255)";
    btn1.style.backgroundColor = "rgb(54, 255, 111)";
}
