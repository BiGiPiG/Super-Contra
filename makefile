%.o: %.cpp
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning up..."
	del /F *.o
	del /F libraylib.a
	del /F $(TARGET)

# Execute makefile (generic)
run: all
	@echo "Running the program..."
	@if exist "$(TARGET)" ( \
		$(TARGET) \
	) else ( \
		echo "Executable not found!" \
	)

.PHONY: all clean run