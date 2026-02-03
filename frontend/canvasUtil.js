
export function clearCanvas() {
    const canvas = document.getElementById("graph");
    const ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}

export function drawNode(ctx, x, y, radius, fill, stroke, strokeWidth, id) {
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

//draw the edges
export function drawLine(ctx, n1, n2, color, weight = null) {
    ctx.beginPath();
    ctx.moveTo(n1.x, n1.y);
    ctx.lineTo(n2.x, n2.y);
    ctx.strokeStyle = color;
    ctx.lineWidth = 2;
    ctx.stroke();

    if (weight !== null) {
        const midX = (n1.x + n2.x) / 2;
        const midY = (n1.y + n2.y) / 2;
        ctx.fillStyle = "black";
        ctx.font = "12px Arial";
        ctx.fillText(weight, midX, midY);
    }
}