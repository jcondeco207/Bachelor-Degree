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
        paused: false,

        truck: {
            x: 900,
            y: 350,
            vx: -2, //velocidade negativa -> right - left
            vy: -2,
            wheels:{
                angle: 0.0,
                angle_step: -0.02 * Math.PI,
            },

           safeDistance : 300,
        
        },

        roadLines: {
            x: 0,
            y: 400,
            xarr: [0, 100 , 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100],
        },

        /*robberArm:{
            angle:0.0,
            angle_step: -0.02*Math.PI,
        },*/

        chaseCar:{
            x: 100,
            y: 350,
            vx: -3,
            vy: -2,
            wheels:{
                angle: 0.0,
                angle_step: -0.02 * Math.PI,
            }
        }
    }

    document.addEventListener("keypress", (e) => {
        if (e.key === " ") model.paused = !model.paused;
    });

    model.update = update;

    return model;
}


function changeRoad(object){
    if((object.x <= 500 && object.x > 0) && object.y < 450){
        object.vy = 2;
    } 
    else if((object.x <= 1000 && object.x > 500) && object.y > 350){
        object.vy = -2;
    }
    else{
        object.vy = 0;
    }
}

function distance(obj1, obj2){
    return Math.sqrt(Math.pow(obj1.x - obj2.x, 2) + Math.pow(obj1.y - obj2.y, 2));
}
//Aqui faço as contas para alterar as cenas
function update() {
    if(this.paused) return;

    let truck = this.truck;
    let robberArm = this.robberArm;
    let chaseCar = this.chaseCar;

    if(truck.x < -170){ 
        truck.x = 1100;
    }

    if(chaseCar.x < -170){ 
        chaseCar.x = 1100;
    }

    //Mudar de via
    changeRoad(truck);
    changeRoad(chaseCar);

    if(distance(truck, chaseCar) < truck.safeDistance){
        truck.vx -= 0.1;
    }
    else{
        truck.vx = -2;
    }

    if(this.roadLines.x > 1100){
        this.roadLines.x = -200;
    }
    
    this.age += 1;

    truck.x += truck.vx;
    truck.y += truck.vy;
    truck.wheels.angle += truck.wheels.angle_step;

    this.roadLines.x -= truck.vx;

    //robberArm.angle += robberArm.angle_step;

    chaseCar.x += chaseCar.vx;
    chaseCar.y += chaseCar.vy;

}
/**
 * CONTEXT
 */
function new_context() {
    //meter o id do svg que quero animar
    let svg_object = document.getElementById("truck-used");
    let svg_object2 = document.getElementById("wheels");
    let svg_object3 = document.getElementById("line1");
    let svg_object4 = document.getElementById("arm");
    let svg_object5 = document.getElementById("robber");
    let svg_object6 = document.getElementById("chaseCar");

    let context = {
        svg_object: svg_object,
        svg_object2: svg_object2,
        svg_object3: svg_object3,
        svg_object4: svg_object4,
        svg_object5: svg_object5,
        svg_object6: svg_object6,
    };

    context.render = render;

    return context;
}   

function lineMover(rx, ry, object){
    let x;
    
    for(let i = 1; i <= 12; i++){
        
       rx[i-1] += 2;

       if(rx[i - 1] > 1100) rx[i-1] = -100;


       object = document.getElementById("line" + i);
        object.setAttribute(
            "transform", `translate(${rx[i-1]},${ry})`);
    }
}

function render(model) {
    message(`AGE: ${model.age}`);

    /*------------------| Truck |------------------*/
    let tx = model.truck.x;
    let ty = model.truck.y; 

    //Aqui altero os atributos do svg
    this.svg_object.setAttribute(
        "transform", `translate(${tx},${ty})`);

    let deg = (model.truck.wheels.angle) * 180.0 / Math.PI;
    this.svg_object2.setAttribute(
        "transform", `rotate(${deg})`);
    
    /*------------------| Road |------------------*/
    let rx = model.roadLines.xarr;
    let ry = model.roadLines.y;

    lineMover(rx, ry, this.svg_object3);

    /*------------------| Robber |------------------*/
    //let robberDeg = model.robberArm.angle * 180.0 / Math.PI;

    this.svg_object5.setAttribute(
        "transform", `translate(${tx},${ty})`);
    
    /*this.svg_object4.setAttribute(
        "transform", `rotate(10,${tx},${ty})translate(${tx},${ty})`);*/

    /*------------------| Chase Car |------------------*/

    let cx = model.chaseCar.x;
    let cy = model.chaseCar.y; 

    //Aqui altero os atributos do svg
    this.svg_object6.setAttribute(
        "transform", `translate(${cx},${cy})`);
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