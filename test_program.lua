my_array = {}

function biggest(buffer)
    local max_value = -1E6
    for value, data in pairs(buffer) do
        if data > max_value then
            max_value = data
        end
    end
    return max_value
end

function plot_buffer(buffer, width, height)
    local buffer_max = biggest(buffer)
    local height_threshold = (height / buffer_max)
    for y = 1, height, 1 do
        for x = 1, width, 1 do
            if math.ceil(buffer[x] * height_threshold) == y then
                io.write("j")
            else
                io.write(" ")
            end
        end
        io.write("\n")
    end
end

function gen_sine(samples, height, phase)
    for iteration = 0, samples, 1 do
        local value = iteration * 4 * math.pi / samples
        my_array[iteration + 1] = math.sin(value + phase) + 1
    end
    plot_buffer(my_array, samples, height)
end

local clock = os.clock
function sleep(n)
    local t0 = clock()
    while clock() - t0 <= n do end
end

for iteration = 0, 500, 1 do
    local phase = iteration * 2*math.pi / 100
    os.execute("clear")
    gen_sine(100, 40, phase)
    sleep(0.01)
end

value = some_function()
print(value)