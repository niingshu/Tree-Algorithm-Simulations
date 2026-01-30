let treeEdges = [];
fetch("events.json")
    .then(res => res.json())
    .then(data => {
        console.log(data);
        play(data.events);

        document.getElementById("output").textContent =
            JSON.stringify(data, null, 2);
    })

//grab the created canvas in html
const canvas = document.getElementById("graph");
const ctx = canvas.getContext("2d");

//vertices
//draws a node
function drawNode(ctx, x, y, radius, fill, stroke, strokeWidth, id) {
    ctx.beginPath();
    //arc (x,y,radius, startAngle, endAngle, anticlockwise)
    ctx.arc(x,y,radius, 0, 2*Math.PI, false);
    //2*math.pi draws a full circle

    if (fill) {
        ctx.fillStyle = fill;
        ctx.fill();
    }

    if (stroke) {
        ctx.lineWidth = strokeWidth;
        ctx.strokeStyle = stroke;
        ctx.stroke();
    }

    //draw the id of the node on itself
    ctx.fillStyle = "white";
    ctx.font = "14px Arial";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(id,x,y);

}

//example of graph nodes data
const nodes = [
    {id: 0, x: 100, y:100, radius:20, color:'blue'}, //id is the value of the node
    {id: 1, x: 200, y:150, radius:30, color:'yellow'},
    {id: 2, x: 300, y:200, radius:25, color:'green'},
]

function render() {
    ctx.clearRect(0,0, canvas.width, canvas.height);

    //draws all nodes
    nodes.forEach (node => {
        drawNode(ctx, node.x, node.y, node.radius, node.color, 'black', 2, node.id);
    })

    treeEdges.forEach(e=> {
        drawLine(
            nodes.find(n=>n.id === e.u),
            nodes.find(n=>n.id === e.v),
            'black',
            e.weight
        );
    });

}

function highlightNode(id) {
    render(); //reset the frame (so everytime this is called, it changes only 1 node's color_

    const node = nodes.find(n=>n.id === id); //strictly equal
    drawNode(ctx,node.x,node.y,node.radius,'red','black',3);
}

function drawLine(n1, n2, color, weight = null) {
    //draws a line (used for both discovery edge and add to tree
    ctx.beginPath();
    ctx.moveTo(n1.x, n1.y); //start point
    ctx.lineTo(n2.x, n2.y); //end point
    ctx.strokeStyle = color;
    ctx.lineWidth = 2;
    ctx.stroke();
    ctx.closePath();

    if (weight != null) {
        //draw weight text near the middle of the line
        const midX = (n1.x + n2.x) /2;
        const midY = (n1.y + n2.y) /2;
        ctx.fillStyle = "black";
        ctx.font = "12px Arial";
        ctx.fillText(weight, midX, midY);
    }
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

let i = 0;

function play(events) {
    if (i>=events.length) return; //stop condiction

    const e = events[i];

    if (e.action === 1) { //visit_node
        highlightNode(e.u);
    }

    if (e.action === 3) { //add to tree
        treeEdge(e.u, e.v, e.weight);
    }

    if (e.action === 2) { //discovery edge
        addEdge(e.u, e.v, e.weight);
    }

    i++;
    setTimeout(()=>play(events), 800);
}