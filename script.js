let tarefas = [];

let proximoId = 1;


const inputNovaTarefa = document.getElementById('add-nova-tarefa');
const btnAdicionar = document.getElementById('btn-adicionar');
//lista desordenada
const listaDeTarefasUL = document.getElementById('lista-de-tarefas');

function mostrarTarefas() {

    listaDeTarefasUL.innerHTML = '';

    if (tarefas.length === 0) {
        listaDeTarefasUL.innerHTML = '<p>Lista de tarefas vazia!</p>';
        return;
    }

    for (const tarefa of tarefas) {

        const itemTarefa = document.createElement('li');
        itemTarefa.classList.add('item-tarefa');
        itemTarefa.dataset.id = tarefa.id;

        if (tarefa.concluida) {
            itemTarefa.classList.add('concluida');
        }

        itemTarefa.innerHTML = `
            <input type="checkbox" ${tarefa.concluida ? 'checked' : ''}>
            <span class="descricao">${tarefa.descricao}</span>
            <button class="btn-excluir">Excluir</button>
        `;

        listaDeTarefasUL.appendChild(itemTarefa);
    }
}


function adicionarTarefa() {

    const descricao = inputNovaTarefa.value.trim(); 

    if (descricao === '') {
        alert('Por favor, digite a descrição da tarefa.');
        return;
    }

    const novaTarefa = {
        id: proximoId,
        descricao: descricao,
        concluida: false // as tarefas sempre começam como pendentes
    };

    tarefas.push(novaTarefa);
    proximoId++;

    inputNovaTarefa.value = '';

    mostrarTarefas();
}


function marcarStatusTarefa(id_tarefa, novo_status) {

    const tarefaParaAtualizar = tarefas.find(t => t.id === id_tarefa);

    if (tarefaParaAtualizar) {
        tarefaParaAtualizar.concluida = novo_status;
        mostrarTarefas(); 
    }
}


function excluirTarefa(id_tarefa) {

    tarefas = tarefas.filter(t => t.id !== id_tarefa);
    mostrarTarefas();
}



btnAdicionar.addEventListener('click', adicionarTarefa);

inputNovaTarefa.addEventListener('keypress', (event) => {
    if (event.key === 'Enter') {
        adicionarTarefa();
    }
});

listaDeTarefasUL.addEventListener('click', (event) => {

    const elementoClicado = event.target;
    const itemTarefa = elementoClicado.closest('.item-tarefa');

    if (!itemTarefa) return; 

    const idDaTarefa = parseInt(itemTarefa.dataset.id);

    // Se o clique foi no checkbox
    if (elementoClicado.type === 'checkbox') {
        marcarStatusTarefa(idDaTarefa, elementoClicado.checked);
    }

    if (elementoClicado.classList.contains('btn-excluir')) {
        excluirTarefa(idDaTarefa);
    }
});

mostrarTarefas();