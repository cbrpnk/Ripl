-- TODO Should be in a lib somewhere

OSC_FREQ = 0

function midiToHz(note)
    return 440 * 2^((note-69)/12)
end

masterOut = masterOut()
-- End lib


function setup()
    osc = osc()
    send(osc, masterOut, 0)
    melody = {[0] = 65, [1] = 33, [2] = 44, [3] = 75}
end

function loop(time, beat)
    set(osc, OSC_FREQ, midiToHz(melody[math.floor(beat)%#melody]))
end
