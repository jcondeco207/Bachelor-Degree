let aids = new Array();
let page; // => Página atual


/**
 * Função responsável por configurar a barra que recebe o valor máximo desejado de preço das casas na pesquisa
 */
function sliderSetup() {
    var slider = document.getElementById("ranger");
    var max = document.getElementById("maxPrice");
    slider.value = 0;
    max.innerHTML = slider.value + "€";

    slider.oninput = function () {
        max.innerHTML = this.value + "€";
    }
}

/**
 * Função utilizada para obter resultados de pesquisa. O pârametro obrigatório é o tipo e poderá ou não incluir
 * parâmetros de pesquisa avançada.
 * Configura também o comportamento do formulário responsável por obter os resultados de pesquisa e gerar os respetivos
 * anúncios.
 *
 * @param form
 * @returns {boolean}
 */
function getData(form) {
    aids = new Array();
    let tipo = document.getElementById("type").value;
    let zona = document.getElementById("zona").value;
    let anunciante = document.getElementById("seller").value;
    let maxPrice = document.getElementById("ranger").value;
    let detalhes = document.getElementById("detalhes").value;

    let args = "tipo=" + tipo + "&ativo=ativo";
    if(zona != ""){
        args+="&zona=" + zona;
    }
    if(anunciante != ""){
        args+="&anunciante=" + anunciante;
    }
    if(maxPrice != 0){
        args+="&preco=" + maxPrice;
    }

    if(detalhes != ""){
        args+="&detalhes=" + detalhes;
    }

    document.getElementById("searchResults").innerHTML = "";

    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (xhttp.readyState === XMLHttpRequest.DONE) {
            handleData(this.responseText);
            const items = JSON.parse(xhttp.responseText);

            for (let i = 0; i < items.resultados.length; i++) {
                if (items.resultados[i].tipo_alojamento == "") {
                    items.resultados[i].tipo_alojamento = "Indefinido";
                }
                alasql("insert into adds values ('"+tipo+"', '" + items.resultados[i].data + "', '" + items.resultados[i].genero + "', '" + decodeURI(items.resultados[i].detalhes) + "', '" + items.resultados[i].contacto + "','" + decodeURI(items.resultados[i].anunciante) + "', " + items.resultados[i].aid + ", '" + decodeURI(items.resultados[i].zona) + "', '" + items.resultados[i].tipo_alojamento + "', " + items.resultados[i].preco + ", '" + items.resultados[i].estado + "')");
            }
        }
    };

    xhttp.open('POST', 'http://alunos.di.uevora.pt/tweb/t1/roomsearch', true);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    xhttp.send(args);
    if (window.getComputedStyle(toHide).display != "none") {
        showAdvancedSearch();
    }
    return false;
}

/**
 * Executa um pedido ao servidor dos anúncios ativos e inativos e configura o comportamento quando se pretende visualizar
 * pormenores de cada um deles.
 *
 */
function manageData() {
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == XMLHttpRequest.DONE) {
                let ads = JSON.parse(this.responseText);
                console.log(ads);
                for(let ad of ads.inativo){
                    let id = document.createElement("p");
                    id.innerText = ad;
                    id.className = "idCol";
                    let state = document.createElement("p");
                    state.innerText = "Inativo";
                    state.style.color = "red";
                    state.className = "stateCol";
                    state.id = ad;
                    let btnDiv = document.createElement("div");
                    btnDiv.className = "btnCol";
                    let btn = document.createElement("button");
                    btn.className = "tableBtn"
                    btn.innerText = "Ver";
                    btn.id = "btn" + ad;
                    btn.onclick = function () {
                        inactiveModal(ad);
                        return false;
                    }
                    btnDiv.append(btn);

                    let div = document.createElement("div");
                    div.className = "tableRow";
                    div.append(id);
                    div.append(state);
                    div.append(btnDiv);

                    document.getElementById("table").append(div);
                }

                for(let ad of ads.ativo){
                    let id = document.createElement("p");
                    id.innerText = ad;
                    id.className = "idCol";
                    let state = document.createElement("p");
                    state.innerText = "Ativo";
                    state.style.color = "#94ffa8";
                    state.className = "stateCol";
                    state.id = ad;

                    let btnDiv = document.createElement("div");
                    btnDiv.className = "btnCol";
                    let btn = document.createElement("button");
                    btn.className = "tableBtn"
                    btn.innerText = "Ver";
                    btn.id = "btn" + ad;
                    btn.onclick = function () {
                        activeModal(ad);
                        return false;
                    }
                    btnDiv.append(btn);

                    let div = document.createElement("div");
                    div.className = "tableRow";
                    div.append(id);
                    div.append(state);
                    div.append(btnDiv);

                    document.getElementById("table").append(div);
                }
        }
    };
    xhttp.open("POST", "http://alunos.di.uevora.pt/tweb/t1/gereanuncios", true);
    xhttp.send();
}

/**
 * Meio intermediário para ativar o modal que mostra os detalhes e opções referentes aos mesmos.
 *
 * @param ad
 */
function activeModal(ad){
    showModal(ad, "ativo");
}

/**
 * Meio intermediário para ativar o modal que mostra os detalhes e opções referentes aos mesmos.
 *
 * @param ad
 */
function inactiveModal(ad){
    showModal(ad, "inativo");
}

/**
 * Através das informações recolhidas na função getAd() altera a div da classe modal e configura o comportamento dos botões
 * que ativam ou desativam os anúncios (permitindo também alterar a sua descrição.
 *
 * @param id
 * @param state
 */
function showModal(id, state){
    let infos = getAd(id);
    let title = document.createElement("h1");
    title.innerText = id;

    let zona = document.createElement("p");
    zona.innerText = decodeURI(infos.zona);

    let img = document.createElement("img");
    img.setAttribute("src" , "media/índice.jpg");
    img.className = "modalPic";

    //let detalhes = document.createElement("p");
    //detalhes.innerText = infos.detalhes;
    let detalhes = document.createElement("textarea");
    detalhes.value = decodeURI(infos.detalhes);
    detalhes.className = "modalText";

    let anunciante = document.createElement("p");
    anunciante.innerText = "Autor: " + decodeURI(infos.anunciante);

    let btn1 = document.createElement("button");
    btn1.innerText = "Alterar estado";
    btn1.className = "modalBtn";
    btn1.onclick = function (){
        activate(id, state, detalhes.value);
        document.getElementById(id).innerText = (state == "ativo" ? "inativo" : "ativo");
        document.getElementById(id).style.color = (state == "ativo" ? "red" : "#94ffa8");
        document.getElementById("btn" + id).onclick = function (){state == "ativo" ? inactiveModal(id) : activeModal(id);};

    }

    let btn2 = document.createElement("button");
    btn2.innerText = "Fechar";
    btn2.className = "modalBtn";
    btn2.onclick = function () {
        let toDestroy = document.getElementsByClassName("modal");
        for(let modal of toDestroy){
            modal.remove();
        }
    }

    let div = document.createElement("div");
    div.className = "rowModal";

    div.append(btn1);
    div.append(btn2);

    let modal = document.createElement("div");
    modal.className = "modal";
    modal.append(title);
    modal.append(zona);
    modal.append(img);
    modal.append(detalhes);
    modal.append(anunciante)
    modal.append(div);
    //modal.append(btn1);
    //modal.append(btn2);
    document.getElementById("toAdd").append(modal);
}

/**
 * Envia para o servidor as alterações efetuadas aos anúncios
 *
 * @param ad
 * @param state
 * @param details
 */
function activate(ad, state, details){
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == XMLHttpRequest.DONE) {
            alert("Estado do anúncio alterado");
            console.log(xhttp.responseText);
        }
    };
    xhttp.open("POST", "http://alunos.di.uevora.pt/tweb/t1/controloanuncio", true);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhttp.send("aid=" + ad + "&estado=" + (state == "ativo" ? "inativo" : "ativo") + "&descricao=" + normalizeString(details));
}

/**
 * Vai buscar as informações de um anúncio com base no id
 *
 * @param id
 * @returns {*}
 */
function getAd(id){
    let needed;
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == XMLHttpRequest.DONE) {
            let ads = JSON.parse(this.responseText);
            console.log(ads.anuncio);
            needed = ads.anuncio;
        }
    };
    xhttp.open("POST", "http://alunos.di.uevora.pt/tweb/t1/anuncio", false);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhttp.send("aid=" + id);
    return needed;
}

/**
 * Recolhe os dados dos anúncios no servidor, insere-os nas bases de dados e faz uma procura pelos 3 anúncios mais recentes
 *
 * @param type
 * @returns {boolean}
 */
function getTop6(type) {
    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (xhttp.readyState === XMLHttpRequest.DONE) {
            const items = JSON.parse(xhttp.responseText);

            for (let i = 0; i < items.resultados.length; i++) {
                if (items.resultados[i].tipo_alojamento == "") {
                    items.resultados[i].tipo_alojamento = "Indefinido";
                }
                alasql("insert into adds values ('" + type + "', '" + items.resultados[i].data + "', '" + items.resultados[i].genero + "', '" + decodeURI(items.resultados[i].detalhes) + "', '" + items.resultados[i].contacto + "','" + decodeURI(items.resultados[i].anunciante) + "', " + items.resultados[i].aid + ", '" + decodeURI(items.resultados[i].zona) + "', '" + items.resultados[i].tipo_alojamento + "', " + items.resultados[i].preco + ", '" + items.resultados[i].estado + "')");
            }

            let obj = alasql("select * from adds where data in ( SELECT data FROM adds where tipo='"+type+"' and ativo='ativo' order by data desc limit 3 )");
            for (let add of obj) {
                handleObjects(add, (type + "Row"));
            }
        }
    };

    xhttp.open('POST', 'http://alunos.di.uevora.pt/tweb/t1/roomsearch', true);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    xhttp.send('tipo=' + type);

    return false;
}

/**
 * Gera "mini" anúncios com base nas informações dadas.
 *
 * @param obj
 * @param divName
 */
function handleObjects(obj, divName) {

    let title = document.createElement("p");
    title.innerHTML = "Anúncio: " + obj.aid;

    let img = document.createElement("img");
    img.setAttribute("src", "media/índice.jpg");

    let descr = document.createElement("p");
    descr.innerHTML = obj.detalhes;

    let name = document.createElement("p");
    name.innerHTML = obj.anunciante;

    let contact = document.createElement("p");
    contact.innerHTML = obj.anunciante + " | Contacto: " + obj.contacto;

    let div = document.createElement("div");
    div.className = "advertise";
    div.append(title);
    div.append(img);
    div.append(descr);
    div.append(name);
    div.append(contact);
    div.onclick = (event) => {
        goToAdd(obj.aid);
    };
    document.getElementById(divName).append(div);
}

/**
 * Abre a página de um anúncio individualmente
 *
 * @param aid
 */
function goToAdd(aid) {
    let results = alasql("select * from adds where aid=" + aid);
    let args = "";
    results = results[0];

    window.location.replace("Anuncio.html?aid=" + aid + "&detalhes=" + results.detalhes + "&preco=" + results.preco + "&anunciante=" + results.anunciante + "&contacto=" + results.contacto + "&zona=" + results.zona + "&data=" + results.data + "&genero=" + results.genero + "&estado=" + results.estado);
}

/**
 * Adiciona os resultados de pesquisa e, caso necessário, adiciona os botões que lidam com a paginação
 *
 * @param data
 */
function handleData(data) {
    const items = JSON.parse(data);
    page = 1;
    if (items.resultados.length > 4) {
        let btns = document.getElementsByClassName("picBtn");
        btns[0].style.visibility = "visible";
        btns[1].style.visibility = "visible";
        aids = items.resultados;
    }
    else{
        let btns = document.getElementsByClassName("picBtn");
        btns[0].style.visibility = "hidden";
        btns[1].style.visibility = "hidden";
    }
    for (let i = 0; i < items.resultados.length && i < 4; i++) {
        createAid(items.resultados[i]);
    }
}

/**
 * Gera "mini" anúncios
 *
 * @param obj
 */
function createAid(obj) {
    let title = document.createElement("p");
    title.innerHTML = "Anúncio: " + obj.aid;

    let img = document.createElement("img");
    img.setAttribute("src", "media/índice.jpg");

    let descr = document.createElement("p");
    descr.innerHTML = obj.detalhes;

    let price = document.createElement("p");
    price.innerHTML = obj.preco + "€";

    let author = document.createElement("p");
    author.innerHTML = obj.anunciante + " | " + obj.contacto;
    //author.style.textAlign = "center";

    let div = document.createElement("div");
    div.className = "advertise";
    div.append(title);
    div.append(img);
    div.append(price);
    div.append(descr);
    div.append(author);
    div.onclick = (event) => {
        goToAdd(obj.aid);
    };
    document.getElementById("searchResults").append(div);
}

/**
 * Oculta/Mostra os parâmetros de pesquisa avançada
 *
 */
function showAdvancedSearch() {
    let toHide = document.getElementById("toHide");
    let holder = document.getElementById("advancedSearch");
    let searchBar = document.getElementById("searchbar");
    let btn = document.getElementById("filter");

    if (window.getComputedStyle(toHide).display === "none") {
        toHide.style.visibility = "visible";
        toHide.style.display = "block";
        holder.style.backgroundColor = "rgba(23, 35, 56, 1)";
        holder.style.boxShadow = "0 5px 10px rgba(0, 0, 0, 0.588)";
        searchBar.style.backgroundColor = "#777e8f";
        btn.setAttribute("src", "media/xmark-solid.svg");
        sliderSetup();
    } else {
        toHide.style.visibility = "hidden";
        toHide.style.display = "none";
        holder.style.backgroundColor = "transparent";
        holder.style.boxShadow = "none";
        searchBar.style.backgroundColor = "rgba(23, 35, 56, 0.928)";
        btn.setAttribute("src", "media/filter-solid.svg");
        //box-shadow: 0 5px 10px rgba(0, 0, 0, 0.588);

    }
}

/**
 * Obtém o index do último anúncio de uma página
 *
 * @param nPag
 * @returns {number}
 */
function getMaxID(nPag) {
    return nPag * 4;
}

/**
 * Obtém o index do primeiro anúncio de uma página
 *
 * @param nPag
 * @returns {number}
 */
function getMinID(nPag) {
    return (nPag * 4) - 3;
}

/**
 * Altera a página atual (e respetivos anúncios)
 *
 * @param n
 */
function changePage(n) {
    page += n;
    page <= 0 ? page = Math.ceil(aids.length / 4) : page > Math.ceil(aids.length / 4) ? page = 1 : console.log("normal");

    let maxID = getMaxID(page);
    let minID = getMinID(page);

    document.getElementById("searchResults").innerHTML = "";
    for (let i = minID; i <= (aids.length) && i <= maxID; i++) {
        createAid(aids[i - 1]);
    }
}

/**
 * Define o comportamento do formulário que adiciona novos anúncios ao server
 *
 * @returns {boolean}
 */
function submitAid() {

    $("#newAid").submit(function (event) {
        let type = document.forms["newAid"]["typeAdd"].value;
        let findUrl;
        type === "procura" ? findUrl = "http://alunos.di.uevora.pt/tweb/t1/registaprocura" : findUrl = "http://alunos.di.uevora.pt/tweb/t1/registaoferta";

        event.preventDefault();

        // => Definir argumentos
        let $form = $(this),
            a1 = ($form.find("input[name='tipo']").val()),
            a2 = document.forms["newAid"]["genero"].value,//($form.find("input[name='genero']").val()),
            a3 = encodeURI($form.find("input[name='anunciante']").val()),
            a4 = encodeURI($form.find("input[name='zona']").val()),
            a5 = document.forms["newAid"]["tipo_alojamento"].value,//($form.find("input[name='tipo_alojamento']").val()),
            a6 = encodeURI(document.forms["newAid"]["detalhes"].value),//($form.find("input[name='detalhes']").val()),
            a7 = document.forms["newAid"]["contacto"].value,
            a8 = (document.getElementById("maxPrice").innerText).replace('€', ''),
            url = findUrl;

        let posting = $.post(findUrl, {
            tipo: a1,
            genero: a2,
            anunciante: a3,
            zona: a4,
            tipo_alojamento: a5,
            detalhes: a6,
            contacto: a7,
            preco: a8
        });

        posting.done(function (data) {
            alert("Anúncio submetido com sucesso!");
            $("#reset").click();
            let content = $(data).find("#content");
        });
    });
    return true;
}


/**
 * Normaliza uma string
 *
 * @param str
 * @returns {*}
 */
function normalizeString(str) {
    return str.normalize('NFD').replace(/[\u0300-\u036f]/g, '');
}


let slideIndex = 1;

function Slide(n) {
    show(slideIndex += n);
}

/**
 * Função responsável por fazer mudar as fotos de cada anuncio
 *
 * @param n
 */
function show(n) {
    let slides = ["índice.jpg", "room.jpg", "bathroom.jpeg"];
    let i;
    if (n > slides.length) {
        slideIndex = 1
    }
    if (n < 1) {
        slideIndex = slides.length ;
    }

    document.getElementById("pic").setAttribute("src", "media/" + slides[slideIndex - 1]);
}

/**
 * Define o comportamento do formulário que submete novas mensagens
 *
 * @returns {boolean}
 */
function sendMensage() {
    var params = (new URL(window.location)).searchParams;

    document.getElementById("detalhes").innerHTML = params.get('detalhes');
    document.getElementById("preco").innerHTML = params.get('preco') + "€";
    document.getElementById("anunciante").innerHTML = params.get('anunciante');
    document.getElementById("contacto").innerHTML = params.get('contacto');
    document.getElementById("zona").innerHTML = params.get('zona');
    document.getElementById("data").innerHTML = params.get('data');
    document.getElementById("genero").innerHTML = params.get('genero');


    $("#form_msg").submit(function (event) {

        event.preventDefault();
        let $form = $(this),
            a1 = params.get('aid'),//($form.find("input[name='tipo']").val()),
            a2 = encodeURI(normalizeString(document.forms["formMsg"]["sender"].value)),//($form.find("input[name='genero']").val()),
            a3 = encodeURI(normalizeString(document.forms["formMsg"]["msg"].value)),
            url = "http://alunos.di.uevora.pt/tweb/t1/mensagens";

        let posting = $.post("http://alunos.di.uevora.pt/tweb/t1/mensagens", {aid: a1, remetente: a2, msg: a3});

        posting.done(function (data) {
            alert("Mensagem enviada com sucesso!");
            var content = $(data).find("#content");
            document.getElementById("form_msg").reset();
        });
    });
    return true;
}
