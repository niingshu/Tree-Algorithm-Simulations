import {clearCanvas, drawNode, drawLine} from "./canvasUtil.js";

console.log("main.js running")

//canvas event
const canvas = document.getElementById("graph");
const ctx = canvas.getContext("2d");

//made up nodes
const nodes = [
    {id: 0, x: 100, y:100, radius:20, color:'blue'},
    {id: 1, x: 250, y:200, radius:20, color:'blue'},
    {id: 2, x: 400, y:100, radius:20, color:'blue'},
];

let treeEdges = [];
let relaxEdges = [];

//clear and draw nodes
function render() {
    clearCanvas();

    nodes.forEach(n => {
        drawNode(ctx, n.x, n.y, n.radius, n.color, "black", 2, n.id);
    });

    treeEdges.forEach(e => {
        drawLine(ctx,
            nodes.find(n => n.id === e.u),
            nodes.find(n => n.id === e.v),
            "red",
            e.weight
        );
    });

    relaxEdges.forEach(e => {
        drawLine(ctx,
            nodes.find(n => n.id === e.u),
            nodes.find(n => n.id === e.v),
            "gray",
            e.weight
        );
    });
}

function addEdge(u, v, weight) {

    const node1 = nodes.find(n=>n.id === u);
    const node2 = nodes.find(n=>n.id === v);
    drawLine(node1, node2, 'black', weight);
}

function treeEdge(u, v, weight) {
    //do not need to reset the frame (since we want to keep track of the tree)
    treeEdges.push({u,v, weight}); //edge from u to v

    const node1 = nodes.find(n=>n.id === u);
    const node2 = nodes.find(n=>n.id === v);
    drawLine(node1, node2, 'red', weight);

}

function relaxEdge(u, v, weight) {

    relaxEdges.push({u, v, weight});

    const node1 = nodes.find(n=>n.id === u);
    const node2 = nodes.find(n=>n.id === v);
    drawLine(node1, node2, 'gray', weight);
}

function highlightNode(id) {
    render();
    const node = nodes.find(n => n.id === id);
    drawNode(ctx, node.x, node.y, node.radius, "red", "black", 2, node.id);
}

canvas.addEventListener("click", e=> {
    const rect = canvas.getBoundingClientRect();
    const x = e.clientX - rect.left;
    const y = e.clientY - rect.top;

    nodes.push({
        id: nodes.length, x,y, radius:20, color: "blue"
    });

    render();
});

let i = 0;

function play(events) {
    if (i >= events.length) return;

    const e = events[i];

    if (e.action === 1) highlightNode(e.u);
    if (e.action === 3) treeEdge(e.u, e.v, e.weight);
    if (e.action === 4) relaxEdge(e.u, e.v, e.weight);

    i++;
    setTimeout(() => play(events), 700);
}

fetch("events.json")
    .then(res => res.json())
    .then(data => {
        //console.log(data);
        play(data.events);

        document.getElementById("output").textContent =
            JSON.stringify(data, null, 2);
    })

//initial draw
render();