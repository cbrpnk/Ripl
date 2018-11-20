function setup()
    out = master_out()
    osc = osc()
    
    send(osc, out, 0)
end

function loop(time)
    set(osc, 0, math.sin((time/44100)*math.pi*2)*256);
end
