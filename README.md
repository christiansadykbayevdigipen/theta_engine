
# theta_engine
 Engine made at digipen for CS230. Programmed in C.

# Style guide

 1. Functions must be listed by the engine name, theta, then the name of the object, followed by the function purpose, followed by additional information if it is a 'sub-object'. For example, theta_window_init. This outlines the initialize function of the theta_window object. However, theta_window_init_shared_window is the 'override' of theta_window_init, by the 'sub-object' theta_window_shared_window.
 2. Log messages. Fatal log messages should read the name of the function that has failed, followed by the phrase 'has failed.' Then it must follow, 'The reason being, ' and then the reason, followed by the newline character '\n'. For example, THETA_FATAL("theta_window_init_shared_window has failed. The reason being, the API you attempted to initialize the window with has not yet been implemented into theta, or the api value is invalid.\n");
 3. Commenting style guide. Every function and struct must be commented. Structs must have @brief information and @param for each field in the struct. The same with functions.
 4. Uninterpreted data buffers. Every single object that contains information that is hidden, must be called uninterpreted_data, so that the DATA_CAST macro may work properly. If not, the DATA_CAST macro may not work properly.
 5. Structs used to fill in uninterpreted data buffers must have the name of the inherited object name, followed by 'specifics.' For example, "theta_shared_window_specifics." Remember, theta_shared_window inherits theta_window.
