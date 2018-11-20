function setup()
    out = master_out()
    osc = osc()
    send(osc, out, 0)
    melody = {[0] = 65, [1] = 33, [2] = 44, [3] = 75}
end

function midiToFreq(note)
    return 440 * 2^((note-69)/12)
end

function loop(time, beat)
    set(osc, 0, midiToFreq(melody[math.floor(beat*2)%#melody]))
end
