function setup()
    io.write("setup()\n")
    out = master_out()
    --osc = osc()
    --mixer = mixer()
    
    --send(osc, mixer, 0)
    --send(mixer, out, 0)
    
    io.write(out, "\n")
end

function loop()
    --io.write("loop()\n")
    --set(osc, OSC_FREQ, 65)
end
