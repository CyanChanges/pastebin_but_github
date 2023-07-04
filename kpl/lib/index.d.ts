import type { Context } from 'koishi';
import { Logger, Schema, Service } from 'koishi';
declare module 'koishi' {
    interface Context {
        __CHRONO_LAUNCHER__: ChronoLauncherService;
    }
}
export interface Config {
}
export declare const Config: Schema<Config>;
export declare const logger: Logger;
export declare function apply(ctx: Context): void;
export declare class ChronoLauncherService extends Service {
    constructor(ctx: Context);
    token: string;
    start: () => Promise<void>;
}
