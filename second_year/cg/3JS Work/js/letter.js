/*
__        __            _     
\ \      / /__  _ __ __| |___ 
 \ \ /\ / / _ \| '__/ _` / __|
  \ V  V / (_) | | | (_| \__ \
   \_/\_/ \___/|_|  \__,_|___/


                            Trabalho elaborado por João Rodrigo Condeço nº48976 
*/

 
function init(mesh) {
    //
    //  Document
    //
    renderer = new THREE.WebGLRenderer({
        alpha: true
    });
    
    //let size = Math.min(600, 600);
    renderer.setSize(1000, 600);
    let div_container = document.getElementById("container");
    div_container.appendChild(renderer.domElement);
    //
    //  Scene (World, Model)
    //
    scene = new THREE.Scene();
    //
    //  Camera (and TrackballControls)
    //
    camera = new THREE.PerspectiveCamera(
        55, // abertura
        1000 / 600, // proportion largura/altura
        0.1, // corte perto
        10000 // corte longe
    );
    camera.position.set(0, 30, 0);
    camera.lookAt(scene.position);
    controls = new THREE.OrbitControls(camera, renderer.domElement);
    //
    //  Lights
    //  
    let ambient_light = new THREE.AmbientLight(0x7F7F7F);
    scene.add(ambient_light);
    //
    let point_light_1 = new THREE.PointLight(0x3F3F3F);
    point_light_1.position.set(5, 0, 0);
    scene.add(point_light_1);
    // //
    let point_light_2 = new THREE.PointLight(0x3F3F3F);
    point_light_2.position.set(-5, 0, 0);
    scene.add(point_light_2);
    //
    //
    //
    scene.mesh = mesh;

    for(let obj in mesh){
        scene.add(mesh[obj]);
    }
    //scene.add(mesh.j);
    //scene.add(mesh.c);
    //
    //  Return camera, scene, etc
    //
    return {
        camera: camera,
        scene: scene,
        renderer: renderer,
        controls: controls
    }
}

function touchdown(letter){
    if(letter.position.y > 0){
        letter.position.y += letter.vy;
    }
}

function wave(letter){
    if(letter.position.z > 2 || letter.position.z < -2){
        letter.vz *= -1;
    }
    letter.position.z += letter.vz;
}

function wheely(letter){
    if(letter.rotation.x < 2*Math.PI){
        letter.rotation.x += 0.04;
    }

}

function animate(step, modelo) {

    requestAnimationFrame(function () {
        animate(step, modelo);
    });

    let r = modelo.r;
    let a1 = modelo.a1;
    let m = modelo.m;
    let a2 = modelo.a2;
    let d = modelo.d;
    let o = modelo.o1;

    for(let i in modelo){
        wave(modelo[i]);
    }

    if(r.position.y > 0 || r.rotation.x < 2*Math.PI){
        touchdown(r);
        wheely(r);
    }
    else if(a1.position.y > 0 || a1.rotation.x < 2*Math.PI){
        touchdown(a1);
        wheely(a1);
    }
    else if(m.position.y > 0 || m.rotation.x < 2*Math.PI){
        touchdown(m);
        wheely(m);
    }
    else if(a2.position.y > 0 || a2.rotation.x < 2*Math.PI){
        touchdown(a2);
        wheely(a2);
    }
    else if(d.position.y > 0 || d.rotation.x < 2*Math.PI){
        touchdown(d);
        wheely(d);
    }
    else if(o.position.y > 0 || o.rotation.x < 2*Math.PI){
        touchdown(o);
        wheely(o);
    }
    //step.scene.mesh.position.z = 3;
    //step.scene.mesh.position.z = 4;

    //if(r.rotation.x < 2*Math.PI){
    //    r.rotation.x += 0.02
    //}
    
    
    step.controls.update();
    step.renderer.render(step.scene, step.camera);
}

//Faço os desenhos
function model() {
    /*---------------------------------------------*/
    //Letra j

    let j_g = jay();
    let j_m = new THREE.MeshLambertMaterial({
        color: "darkseagreen"
    });

    j_m.side = THREE.DoubleSide;
    let j = new THREE.Mesh(j_g, j_m);
    j.scale.set(1, 1, 1);

    let jObj = new THREE.Object3D();
    jObj.add(j);
    
    //boat.rotation.y = Math.PI / 2;
    jObj.scale.set(1, 1, 1);
    
    /*---------------------------------------------*/
    //Letra c

    let c_g = cay();
    let c_m = new THREE.MeshLambertMaterial({
        color: "blue"
    });

    c_m.side = THREE.DoubleSide;
    let c = new THREE.Mesh(c_g, c_m);
    c.scale.set(1, 1, 1);

    let cObj = new THREE.Object3D();
    cObj.add(c);
    
    //boat.rotation.y = Math.PI / 2;
    cObj.scale.set(1, 1, 1);

    /*---------------------------------------------*/
    //Letra r

    let r_g = ray();
    let r_m = new THREE.MeshLambertMaterial({
        color: "blue"
    });

    r_m.side = THREE.DoubleSide;
    let r = new THREE.Mesh(r_g, r_m);
    r.scale.set(1, 1, 1);

    let rObj = new THREE.Object3D();
    rObj.add(r);
    
    rObj.scale.set(0.9, 1, 1);
    rObj.rotation.set(0, 4.7, 0);
    rObj.position.set(-13,40,-1.2);

    /*---------------------------------------------*/
    //Letra a

    let a_g = antman();
    let a_m = new THREE.MeshLambertMaterial({
        color: "blue"
    });

    a_m.side = THREE.DoubleSide;
    let a = new THREE.Mesh(a_g, a_m);
    a.scale.set(1, 1, 1);

    let a2 = new THREE.Mesh(a_g, a_m);
    a.scale.set(1, 1, 1);

    let aObj = new THREE.Object3D();
    aObj.add(a);

    let aObj2 = new THREE.Object3D();
    aObj2.add(a2);
    
    //boat.rotation.y = Math.PI / 2;
    aObj.scale.set(2, 1, 2);
    aObj2.scale.set(2, 1, 2);
    aObj.rotation.set(0, 4.7, 0);
    aObj2.rotation.set(0, 4.7, 0);
    aObj.position.set(-8.5,40,0);
    aObj2.position.set(1,40,1.6);

    /*---------------------------------------------*/
    //Letra m

    let m_g = may();
    let m_m = new THREE.MeshLambertMaterial({
        color: "blue"
    });

    m_m.side = THREE.DoubleSide;
    let m = new THREE.Mesh(m_g, m_m);
    m.scale.set(1, 1, 1);

    let mObj = new THREE.Object3D();
    mObj.add(m);
    
    //boat.rotation.y = Math.PI / 2;
    mObj.scale.set(1.5, 1, 1.5);
    mObj.rotation.set(0, 4.7, 0);
    mObj.position.set(-3.4, 40, 1.2);

    /*---------------------------------------------*/
    //Letra d

    let d_g = day();
    let d_m = new THREE.MeshLambertMaterial({
        color: "blue"
    });

    d_m.side = THREE.DoubleSide;
    let d = new THREE.Mesh(d_g, d_m);
    d.scale.set(1, 1, 1);

    let dObj = new THREE.Object3D();
    dObj.add(d);
    
    //boat.rotation.y = Math.PI / 2;
    dObj.scale.set(1.9, 1, 2);
    dObj.rotation.set(0, 4.7, 0);
    dObj.position.set(5, 40, 0.4);

    
    /*---------------------------------------------*/
    //Letra o

    let o_g = donut();
    let o_m = new THREE.MeshLambertMaterial({
        color: "blue"
    });

    o_m.side = THREE.DoubleSide;
    let o = new THREE.Mesh(o_g, o_m);
    let o2 = new THREE.Mesh(o_g, o_m);

    let oObj = new THREE.Object3D();
    oObj.add(o);
    
    //boat.rotation.y = Math.PI / 2;
    oObj.scale.set(2, 1, 2);
    oObj.position.set(10, 40, -0.8);

    /*---------------------------------------------*/

    let abc = {
        r: rObj,
        a1: aObj,
        a2: aObj2,
        m: mObj,
        d: dObj,
        o1: oObj,
    };
    

    return abc;

}

function jay(){
    let coordinates = [
        new THREE.Vector4(-8, 2, 1),
        new THREE.Vector4(-4, 2, 1),
        new THREE.Vector4(-4, 6, 1),
        new THREE.Vector4(-8, 6, 1),
        
    ];

    let faces = [
        new THREE.Face4(0, 1, 2, 3, 4),
        

    ]

    let j = new THREE.Geometry();
    j.vertices = coordinates;
    j.faces = faces;
    j.computeFaceNormals(); // get the right "outside"
    j.computeBoundingSphere(); // to help the rendering system
    return j;
}

function cay(){
    let cross_section_points = [
        new THREE.Vector2(2, 0),
        new THREE.Vector2(2, 1),
        new THREE.Vector2(1, 1),
        new THREE.Vector2(1, 3),
        new THREE.Vector2(2, 3),
        new THREE.Vector2(2, 4),
        new THREE.Vector2(0, 4),
        new THREE.Vector2(0, 2),
        new THREE.Vector2(0, 0),
        new THREE.Vector2(1, 0),
    ];

    let cross_section = new THREE.Shape(cross_section_points);
    //
    //  Spine
    //
    let spine_points = [
        new THREE.Vector3(0, -1, 0),
        new THREE.Vector3(0, 1, 0)
    ];
    //
    let spine = new THREE.CatmullRomCurve3(spine_points);
    //
    let parameters = {
        extrudePath: spine // <-- the spine goes here
    };
    //
    //  Geometry
    //
    return new THREE.ExtrudeBufferGeometry(cross_section, parameters);
}

function ray(){
    let cross_section_points = [
        new THREE.Vector2(-1, -2),
        new THREE.Vector2(0.42, -2),
        new THREE.Vector2(0.46, 1),
        new THREE.Vector2(1.02, 1.62),
        new THREE.Vector2(2, 1.82),
        new THREE.Vector2(3.02, 1.66),
        new THREE.Vector2(3.04, 2.26),
        new THREE.Vector2(2, 2.44),
        new THREE.Vector2(0.98, 2.24),
        new THREE.Vector2(0, 1.6),
        new THREE.Vector2(-0.3, 2.44),
        new THREE.Vector2(-1.26, 2.42),
        new THREE.Vector2(-0.98, 1.62),
    ];

    let cross_section = new THREE.Shape(cross_section_points);
    //
    //  Spine
    //
    let spine_points = [
        new THREE.Vector3(0, -1, 0),
        new THREE.Vector3(0, 1, 0)
    ];
    //
    let spine = new THREE.CatmullRomCurve3(spine_points);
    //
    let parameters = {
        extrudePath: spine // <-- the spine goes here
    };
    //
    //  Geometry
    //
    return new THREE.ExtrudeBufferGeometry(cross_section, parameters);
}

function antman(){
    
    const shape = new THREE.Shape();
    shape.moveTo(0.61655, -0.99478);
    shape.lineTo(0.87243, -0.99478);
    shape.lineTo(0.86674, 0.59163);
    shape.lineTo(0.60895, 0.80287);
    shape.lineTo(0.40126, 0.90671);
    shape.lineTo(0.10067, 1.01055);
    shape.lineTo(-0.09609, 1.00509);
    shape.lineTo(-0.31596, 0.9726);
    shape.lineTo(-0.5036, 0.87593);
    shape.lineTo(-0.69729, 0.70449);
    shape.lineTo(-0.86182, 0.51771);
    shape.lineTo(-0.98692, 0.31301);
    shape.lineTo(-1, 0);
    shape.lineTo(-0.92437, -0.30108);
    shape.lineTo(-0.82771, -0.49441);
    shape.lineTo(-0.69729, -0.69466);
    shape.lineTo(-0.53203, -0.83557);
    shape.lineTo(-0.32733, -0.93223);
    shape.lineTo(-0.10155, -0.98979);
    shape.lineTo(0.1116, -0.99526);
    shape.lineTo(0.30289, -0.90235);
    shape.lineTo(0.49964, -0.7985);
    shape.lineTo(0.61087, -0.61381);
    
    let hole = new THREE.Shape();
    hole.moveTo(0.50283, -0.29539);
    hole.lineTo(0.50283, 0.18792);
    hole.lineTo(0.5, 0.5);
    hole.lineTo(0.38911, 0.59163);
    hole.lineTo(0.22422, 0.70535);
    hole.lineTo(0.08206, 0.75653);
    hole.lineTo(-0.09989, 0.77359);
    hole.lineTo(-0.28753, 0.71672);
    hole.lineTo(-0.48654, 0.59732);
    hole.lineTo(-0.60026, 0.42674);
    hole.lineTo(-0.67987, 0.26184);
    hole.lineTo(-0.685, 0);
    hole.lineTo(-0.66281, -0.18736);
    hole.lineTo(-0.58889, -0.36931);
    hole.lineTo(-0.5, -0.5);
    hole.lineTo(-0.32733, -0.63087);
    hole.lineTo(-0.08852, -0.71616);
    hole.lineTo(0.09912, -0.71048);
    hole.lineTo(0.29813, -0.59675);
    hole.lineTo(0.40048, -0.49441);
    
    shape.holes.push( hole );

    let spine_points = [
        new THREE.Vector3(0, -1, 0),
        new THREE.Vector3(0, 1, 0)
    ];
    //
    let spine = new THREE.CatmullRomCurve3(spine_points);
    //
    let parameters = {        
        extrudePath: spine, // <-- the spine goes here

    };
    
    const geometry = new THREE.ExtrudeGeometry( shape, parameters );

    return geometry;
    
}

function may(){
    
    const shape = new THREE.Shape();
    shape.moveTo(-2, -1.3);
    shape.lineTo(-2, 0.7);
    shape.lineTo(-2.0988, 1.00483);
    shape.quadraticCurveTo(-2, 1.2, -1.69958, 1.10463);
    shape.lineTo(-1.49998, 1.01731);
    shape.lineTo(-1.49998, 1.01731);
    shape.quadraticCurveTo(-1, 1.2, -0.4957, 1.10463);
    shape.lineTo(0 , 1.10463); //N
    shape.quadraticCurveTo(0.5, 1.2, 0.99512, 1.10463); // T
    shape.quadraticCurveTo(1.41, 0.96, 1.5, 0.7); // U
    shape.lineTo(1.5 , -1.3); //P
    shape.lineTo(1, -1.3); //O
    shape.lineTo(1, 0.7); //S
    shape.quadraticCurveTo(0.5, 0.9, 0, 0.7); // K
    shape.lineTo(0, -1.3); //I
    shape.lineTo(-0.5, -1.3); //H
    shape.lineTo(-0.5, 0.7); //J
    shape.quadraticCurveTo(-1, 0.9, -1.5, 0.7); // D
    shape.lineTo(-1.5, -1.3); //J


    let spine_points = [
        new THREE.Vector3(0, -1, 0),
        new THREE.Vector3(0, 1, 0)
    ];
    //
    let spine = new THREE.CatmullRomCurve3(spine_points);
    //
    let parameters = {        
        extrudePath: spine, // <-- the spine goes here

    };
    
    const geometry = new THREE.ExtrudeGeometry( shape, parameters );

    return geometry;
    
}

function day(){
    
    const shape = new THREE.Shape();
    shape.moveTo(0, -1); //A

    shape.quadraticCurveTo(-1.01, -0.8, -1, 0); //
    shape.quadraticCurveTo(-1.01, 0.8, 0, 1.0); //B

    shape.quadraticCurveTo(0.8, 0.9, 1.01, 0.4); //F
    shape.lineTo(1.01 , -0.4); // C
    shape.quadraticCurveTo(0.8, -0.9, 0, -1); // A
    
    shape.moveTo(0.8, -0.8); //G
    shape.lineTo(0.8 , 1.5); //J
    shape.quadraticCurveTo(1.05, 1.7, 1.3, 1.5); // I
    shape.lineTo(1.3, -0.8); //H
    shape.quadraticCurveTo(1.05, -1.23, 0.8, -0.8); // G


    let hole = new THREE.Shape();
    hole.arc(0, 0, 0.6, 0, 2 * Math.PI);

    shape.holes.push( hole );
    


    let spine_points = [
        new THREE.Vector3(0, -1, 0),
        new THREE.Vector3(0, 1, 0)
    ];
    //
    let spine = new THREE.CatmullRomCurve3(spine_points);
    //
    let parameters = {        
        extrudePath: spine, // <-- the spine goes here

    };
    
    const geometry = new THREE.ExtrudeGeometry( shape, parameters );

    return geometry;
    
}

function donut(){
    
    const shape = new THREE.Shape();
    shape.arc(0, 0, 1.0, 0, 2 * Math.PI);

    let hole = new THREE.Shape();
    hole.arc(0, 0, 0.5, 0, 2 * Math.PI);

    shape.holes.push( hole );

    let spine_points = [
        new THREE.Vector3(0, -1, 0),
        new THREE.Vector3(0, 1, 0)
    ];
    //
    let spine = new THREE.CatmullRomCurve3(spine_points);
    //
    let parameters = {        
        extrudePath: spine, // <-- the spine goes here

    };
    
    const geometry = new THREE.ExtrudeGeometry( shape, parameters );

    return geometry;
    
}

function main() {
    

    let step = init(model());

    let modelo = {
        r:{
            position: step.scene.mesh.r.position,
            rotation: step.scene.mesh.r.rotation,
            vx: 0,
            vy: -0.30,
            vz: 0.08,

        },

        a1:{
            position: step.scene.mesh.a1.position,
            rotation: step.scene.mesh.a1.rotation,
            vx: 0,
            vy: -0.30,
            vz: 0.08,

        },

        m:{
            position: step.scene.mesh.m.position,
            rotation: step.scene.mesh.m.rotation,
            vx: 0,
            vy: -0.30,
            vz: 0.08,

        },

        a2:{
            position: step.scene.mesh.a2.position,
            rotation: step.scene.mesh.a2.rotation,
            vx: 0,
            vy: -0.15,
            vz: -0.08,

        },

        d: {
            position: step.scene.mesh.d.position,
            rotation: step.scene.mesh.d.rotation,
            vx: 0,
            vy: -0.15,
            vz: -0.08,

        },

        o1:{
            position: step.scene.mesh.o1.position,
            rotation: step.scene.mesh.o1.rotation,
            vx: 0,
            vy: -0.15,
            vz: -0.08,

        }
    }

    animate(step, modelo);
}


/**Coordenadas corretas
 * R -> (-13,0,0.2)
 * A -> (-8.5,0,0)
 * M -> (-3.4,0,0.5)
 * A -> (1,0,0)
 * D -> (5,0,0)
 * O -> (10,0,0)
 */