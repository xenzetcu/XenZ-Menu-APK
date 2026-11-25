#include <jni.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <android/log.h>
#include <EGL/egl.h>
#include "Menu/Menu.h"
#include "Hacks/hooks.h"
#include "And64InlineHook/And64InlineHook.hpp"

void (*original_Update)(void* instance) = nullptr;
void hooked_Update(void* instance) {
    if (original_Update != nullptr) original_Update(instance);
}

EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    if (!Menu::init) { Menu::Setup(); Menu::init = true; }
    Menu::Draw();
    return old_eglSwapBuffers(dpy, surface);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    return JNI_VERSION_1_6;
}

__attribute__((constructor))
void lib_main() {
    auto eglhandle = dlopen("libEGL.so", RTLD_LAZY);
    auto eglSwapBuffers = dlsym(eglhandle, "eglSwapBuffers");
    A64HookFunction(eglSwapBuffers, (void*)hook_eglSwapBuffers, (void**)&old_eglSwapBuffers);
}
