function format_text(content, cursorRow, cursorColumn, currentLine, previousCursorColumn)
    -- Brackets to check
    local openingBrackets = {'(', '{', '['}
    local closingBrackets = {['('] = ')', ['{'] = '}', ['['] = ']'}
    
    -- If the cursor is moving backward, do nothing
    if previousCursorColumn and cursorColumn < previousCursorColumn then
        return content
    end

    -- Check if the cursor is at the end of the line and if there's an opening bracket
    local currentChar = currentLine:sub(cursorColumn, cursorColumn)
    
    -- If an opening bracket is typed
    for _, opening in ipairs(openingBrackets) do
        if currentChar == opening then
            -- Check if the next character is already the corresponding closing bracket
            local nextChar = currentLine:sub(cursorColumn + 1, cursorColumn + 1)
            local closing = closingBrackets[opening]
            
            if nextChar ~= closing then
                -- Insert closing bracket
                local newContent = content:sub(1, cursorColumn) .. closing .. content:sub(cursorColumn + 1)
                
                -- Adjust cursor position to be between the opening and closing brackets
                local newCursorPosition = cursorColumn + 1
                return newContent, newCursorPosition
            else
                -- If the closing bracket is already there, just move the cursor forward
                local newCursorPosition = cursorColumn + 1
                return content, newCursorPosition
            end
        end
    end

    -- If no bracket detected, return the content as is
    return content
end